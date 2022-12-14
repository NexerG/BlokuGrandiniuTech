#pragma once
#include <string>
#include "sha256.h"

using std::string;

class Transaction
{

public:
	string GetTransId();
	string GetPubKSender();
	string GetPubKRec();
	double GetSum();
	string GetSumStr();
	
	void SetSum(double value);
	void SetPubKSen(string value);
	void SetPubKRec(string value);
	void genHash();

private:
	string TransId, PubKSender, PubKReceiver;
	double Sum;
};

