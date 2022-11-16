#include "Vartotojas.h"

string Vartotojas::GetPubK()
{
	return PubK;
}

void Vartotojas::SetPubK(string value)
{
	this->PubK = value;
}

string Vartotojas::GetName()
{
	return Name;
}

double Vartotojas::GetBal()
{
	return Balance;
}

void Vartotojas::SetName(string value)
{
	this->Name = value;
}

void Vartotojas::SetBal(double value)
{
	this->Balance = value;
}
