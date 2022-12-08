#include "Blokas.h"

string Blokas::GetHash()
{
    return Hash;
}

string Blokas::GetPrevHash()
{
    return PrevHash;
}

vector<Transaction> Blokas::GetTrans()
{
    return TransList;
}

void Blokas::SetPrevHash(string value)
{
    this->PrevHash = value;
}

void Blokas::SetVersion(string value)
{
    this->Version = value;
}

void Blokas::SetTime(string value)
{
    this->Time = value;
}

//void Blokas::SetVersion(string value)
//{
//    this->Version = value;
//}

void Blokas::SetDiffTarget(int value)
{
    this->DiffTarget = value;
}

void Blokas::SetTrans(vector<Transaction> Trans)
{
    for (int i = 0; i < Trans.size(); i++)
    {
        this->TransList.push_back(Trans[i]);
    }
}

void Blokas::AddTransaction(Transaction Trans)
{
    this->TransList.push_back(Trans);
}

void Blokas::CalcMerkle()
{
    Hashinimas Darom;

    string L1, L2, L3, L4;
    vector<string>KaHash;
    vector<Transaction>Trans = GetTrans();
    for (int i = 0; i < Trans.size(); i++)
    {
        L1 = Darom.darom(Trans[i].GetPubKSender(), 32);
        L2 = Darom.darom(Trans[i].GetPubKRec(), 32);
        L3 = Darom.darom(Trans[i].GetSumStr(), 32);
        L4 = Darom.darom(Trans[i].GetTransId(), 32);

        KaHash.push_back(Darom.darom(L1 + L2 + L3 + L4, 64));
    }
    Trans.clear();

    for (int i = KaHash.size()-1; i >= 0; i--)
    {
        string trumpas;
        trumpas.append(KaHash[0]);
        trumpas.append(KaHash[i]);
        KaHash[0] = Sha256(trumpas);
    }

    this->MerkelRHash = KaHash[0];
    KaHash.clear();
}

void Blokas::Mine(int trukme)
{
    CalcMerkle();

    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    while (duration.count() < trukme && Nonce < UINT64_MAX)
    {
        string MetaD;
        MetaD.append(PrevHash);
        MetaD.append(Time);
        MetaD.append(Version);
        MetaD.append(MerkelRHash);
        MetaD.append(to_string(Nonce));
        string hash = Sha256(MetaD);
        string dummy;

        for (int i = 0; i < DiffTarget; i++)
        {
            dummy.append("0");
        }

        if (hash.substr(0, DiffTarget) == dummy)
        {
            Hash = hash;
            break;
        }

        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);

        Nonce++;
    }
}

void Blokas::Update(vector<Vartotojas> Vart)
{
    vector<string> PKs;
    vector<string>::iterator it;
    for(int i=0;i<Vart.size();i++)
    {
        PKs.push_back(Vart[i].GetPubK());
    }

    for (int i = 0; i < TransList.size(); i++)
    {
        it = find(PKs.begin(), PKs.end(), TransList[i].GetPubKSender());
        if (it != PKs.end())
            Vart[it - PKs.begin()].SetBal(Vart[it - PKs.begin()].GetBal() - TransList[i].GetSum());

        it = find(PKs.begin(), PKs.end(), TransList[i].GetPubKRec());
        if (it != PKs.end())
            Vart[it - PKs.begin()].SetBal(Vart[it - PKs.begin()].GetBal() + TransList[i].GetSum());
    }
}

void Blokas::BalCheck(vector<Vartotojas> Vart)
{
    vector<string> PKs;
    vector<string>::iterator it;
    vector<int>r;
    for (int i = 0; i < Vart.size(); i++)
    {
        PKs.push_back(Vart[i].GetPubK());
    }

    for (int i = 0; i < TransList.size(); i++)
    {
        it = find(PKs.begin(), PKs.end(), TransList[i].GetPubKSender());
        if (it != PKs.end())
        {
            if (Vart[it-PKs.begin()].GetBal()<TransList[i].GetSum())
            {
                r.push_back(i);
            }
        }
    }

    for (int i = r.size()-1; i >= 0; i--)
    {
        TransList.erase(TransList.begin() + r[i]);
    }
}

Blokas::Blokas(vector<Transaction> Trans, string Vers, int diff, vector<Vartotojas> Vart, Blokas Praeitas)
{
    SetTrans(Trans);
    BalCheck(Vart);

    if (Praeitas.Hash != "")
        PrevHash = Praeitas.Hash;
    else PrevHash = "Root";

    
    stringstream ss;
    ss << time(NULL);
    SetTime(ss.str());

    SetVersion(Vers);
    SetDiffTarget(diff);

    Mine(5000);
    if (Hash != "")
    {
        cout << Hash << endl;
        Update(Vart);
    }
    else
        cout << "Blokas neiskastas" << endl;
}

Blokas::Blokas(string roothash)
{
}