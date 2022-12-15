#pragma once
#include <string>
#include "Transactions.h"
#include <vector>
#include <chrono>
#include <sstream>
#include "Hashinimas.h"
#include <bitset>
#include <algorithm>
#include "Vartotojas.h"
#include "sha256.h"

using std::string;
using std::vector;
using std::stringstream;
using std::to_string;
using std::find;
using namespace std::chrono;

class Blokas
{
public:
	Blokas(vector<Transaction> Trans, string Vers, int diff, vector<Vartotojas> Vart, Blokas Praeitas);
	Blokas(string roothash);
	string GetHash();
	string GetPrevHash();
	string GetMerkle();
	vector<Transaction> GetTrans();

private:
	string Hash, PrevHash, Time, Version, MerkelRHash;
	vector<Transaction> TransList;
	uint64_t Nonce = 0;
	int DiffTarget;

	void SetPrevHash(string value);
	void SetVersion(string value);
	void SetTime(string value);
	//void SetVersion(string value);
	void SetDiffTarget(int value);
	void SetTrans(vector<Transaction> Trans);
	void AddTransaction(Transaction Trans);

	void CalcMerkle();
	vector<string> Dalinam(vector<string> Duomenys);

	void Mine(int trukme);
	void Update(vector<Vartotojas> Vart);
	void BalCheck(vector<Vartotojas> Vart);

};

