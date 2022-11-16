#pragma once
#include <string>

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

private:
	string TransId, PubKSender, PubKReceiver;
	double Sum;
};

