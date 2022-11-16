#include "Transactions.h"
#include <bitset>

using std::to_string;

string Transaction::GetTransId()
{
	return TransId;
}

string Transaction::GetPubKSender()
{
	return PubKSender;
}

string Transaction::GetPubKRec()
{
	return PubKReceiver;
}

double Transaction::GetSum()
{
	return Sum;
}

string Transaction::GetSumStr()
{
	return to_string(Sum);
}

void Transaction::SetSum(double value)
{
	this->Sum = value;
}

void Transaction::SetPubKSen(string value)
{
	this->PubKSender = value;
}

void Transaction::SetPubKRec(string value)
{
	this->PubKReceiver = value;
}
