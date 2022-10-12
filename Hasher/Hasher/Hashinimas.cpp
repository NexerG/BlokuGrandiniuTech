#include "Hashinimas.h"

string atkonvertavimas(string bitai)
{
	string HexZodis;

	if (bitai.length() > 8)
		for (int i = 0; i < bitai.length(); i = i + 9)
		{
			bitset<8> raide(bitai.substr(i, 8));
			stringstream ss;
			ss << hex << raide.to_ullong();
			HexZodis += ss.str();
		}
	else
	{
		bitset<8> raide(bitai);
		stringstream ss;
		ss << hex << raide;
		HexZodis += ss.str();
	}

	return HexZodis;
}

string Rotacija(string veiksnys, int ZUniKodas)
{
	if (ZUniKodas % 3 == 0)
	rotate(veiksnys.begin(), veiksnys.begin() + 7, veiksnys.end());
	else if (ZUniKodas % 3 == 1)
		rotate(veiksnys.begin(), veiksnys.begin() + 5, veiksnys.end());
	else if (ZUniKodas % 3 == 2)
		rotate(veiksnys.begin(), veiksnys.begin() + 3, veiksnys.end());
	else
		rotate(veiksnys.begin(), veiksnys.begin() + 1, veiksnys.end());

	return veiksnys;
}

void Hashinimas::darom(string zodis, int HashIlgis)
{
	Konstantos Konst;
	int ZUniKodas = 0;

	for (int i = 0;i < zodis.length();i++)
	{
		ZUniKodas += (int)zodis[i];
	}

	if (zodis.length() < HashIlgis)
	{
		//datraukiam zodi iki reikiamo ilgio per konstantas
		for (size_t i = zodis.length(); i < HashIlgis; i++)
		{
			zodis += Konst.Konst[i];
		}
	}

	if (zodis.length() > HashIlgis)
	{
		//sutrumpinam stringa iki reikiamo ilgio
		for (size_t i = zodis.length(); i > HashIlgis; i--)
		{
			zodis[i - HashIlgis] = (int)zodis[i - HashIlgis] / ((int)zodis[i]+1);
			zodis.pop_back();
		}
	}

	string bitai;
	for (size_t i = 0; i < zodis.size(); i++)
	{
		string rotuojam = bitset<8>(zodis[i]).to_string();

		int BitUniKodas = (int)zodis[i] + ZUniKodas;
		//rotuojam bitus
		rotuojam = Rotacija(rotuojam, BitUniKodas);

		bitai += rotuojam + " ";
	}

	cout << endl << atkonvertavimas(bitai) << endl;
}