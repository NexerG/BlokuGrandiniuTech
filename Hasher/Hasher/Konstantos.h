#pragma once
#include <string>
using namespace std;

class Konstantos
{
public:
	int Konst[64];

	void pirminiai(int Konst[]);
	bool isPrime(int n);

	Konstantos()
	{
		pirminiai(Konst);
	}
};

