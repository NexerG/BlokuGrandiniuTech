#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include "Konstantos.h"
using namespace std;

int HashIlgis=32; //turi buti dvigubai mazesnis uz Hash ilgi nes HexaDecimal yra sudarytas is 2 simboliu

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
	Konstantos Konst;

	int startas;
	cout << "Pasirinkite kaip norite atlikti hash.\n1. Ivedimas ranka\n2. Is failo";
	cin >> startas;
	if(startas==1)
		cin >> zodis;
	else if (startas == 2)
	{
		int automatizuotas;
		cout << endl<<"1. 2 failai su 1000 skirtingai sugeneruotu simboliu kurie labai skiriasi\n2. 2 failai su 1000 skirtingai sugeneruotu simboliu, kurie beveik nesiskiria\n3. 2 failai kuriuose po 1 skirtinga simboli";
		cin >> automatizuotas;
		if (automatizuotas == 1)
		{

		}
		else if (automatizuotas == 2)
		{

		}
		else if (automatizuotas == 3)
		{

		}
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
		//datraukiam zodi iki reikiamo ilgio per konstantas
		for (size_t i = zodis.length(); i > HashIlgis; i--)
		{
			zodis[i - HashIlgis] = (int)zodis[i - HashIlgis] / (int)zodis[i-1];
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

	cout << atkonvertavimas(bitai);
}