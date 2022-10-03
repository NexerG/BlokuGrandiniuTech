#include "Konstantos.h"
#include <bitset>

void Konstantos::pirminiai(int Konst[])
{
	//uzpildom masyva pirmais 64 pirminiais skaiciais (pradedant nuo 2)
	int prime = 2;
	for (int i = 0; i < 64; i++)
	{
		while (!isPrime(prime))
			prime++;
		Konst[i] = prime;
	}
}

bool Konstantos::isPrime(int n)
{
	if(n<=1)
		return false;
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return false;

	return true;
}

