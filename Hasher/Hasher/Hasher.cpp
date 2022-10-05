#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include "Konstantos.h"
using namespace std;

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
			cout << ss.str() << endl;
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

string Rotacija(string veiksnys, size_t i)
{
	if (i % 3 == 0)
	rotate(veiksnys.begin(), veiksnys.begin() + 7, veiksnys.end());
	else if (i % 3 == 1)
		rotate(veiksnys.begin(), veiksnys.begin() + 5, veiksnys.end());
	else if (i % 3 == 2)
		rotate(veiksnys.begin(), veiksnys.begin() + 3, veiksnys.end());
	else
		rotate(veiksnys.begin(), veiksnys.begin() + 1, veiksnys.end());

	return veiksnys;
}


int main()
{
	string zodis;
	cin >> zodis;
	Konstantos Konst;

	if (zodis.length() < 64)
	{
		//dametam iki 64
		for (size_t i = zodis.length(); i < 64; i++)
		{
			zodis += Konst.Konst[i];
		}
	}

	else if (zodis.length() > 64)
	{
		//sumazinam iki 64
		for (size_t i = zodis.length(); i > 64; i--)
		{
			zodis[i - 64] = (int)zodis[i - 64] / (int)zodis[i];
		}
	}

	string bitai;
	for (size_t i = 0; i < zodis.size(); i++)
	{
		if (i % 2 == 0)
		{
			zodis[i] = (int)zodis[i];
		}
		string rotuojam = bitset<8>(zodis[i]).to_string();

		//rotuojam bitus
		rotuojam = Rotacija(rotuojam, i);

		bitai += rotuojam + " ";
	}

	//debug
	cout << atkonvertavimas(bitai);

	//string Hashas = atkonvertavimas(bitai);
	//cout << Hashas;
}