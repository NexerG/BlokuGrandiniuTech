#pragma once
#include <string>

using std::string;

class Vartotojas
{
public:
	
	string GetPubK();
	string GetName();
	double GetBal ();

	void SetPubK(string value);
	void SetName(string value);
	void SetBal(double value);

private:
	string Name, PubK;
	double Balance;
};

