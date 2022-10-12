#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "Hashinimas.h"
using namespace std;

const int HashIlgis = 32; //turi buti dvigubai mazesnis uz Hash ilgi nes HexaDecimal yra sudarytas is 2 simboliu
void generuojamF(int generacija);

int main()
{
	string zodis;
	Hashinimas veiksmas;
	string pavad1, pavad2;


	int startas;
	cout << "Pasirinkite kaip norite atlikti hash.\n1. Ivedimas ranka\n2. Is failo\n";
	cin >> startas;
	if (startas == 1)
	{
		cin >> zodis;
		veiksmas.darom(zodis, HashIlgis);
	}

	else if (startas == 2)
	{
		int generacija;
		int automatizuotas;
		//string zodis1, zodis2;

		cout << endl<<"1. 2 failai su 1000 skirtingai sugeneruotu simboliu kurie labai skiriasi\n2. 2 failai su 1000 skirtingai sugeneruotu simboliu, kurie beveik nesiskiria\n3. 2 failai kuriuose po 1 skirtinga simboli";
		cin >> automatizuotas;

		cout << "ar generuoti failus? 1- Taip. 2- Ne.";
		cin >> generacija;
		if (generacija == 1)
			generuojamF(automatizuotas);

		if (automatizuotas == 1)
		{
			ifstream fs1("Hasher1.txt");
			ifstream fs2("Hasher2.txt");

			if (fs1.good() && fs2.good())
			{
				fs1 >> zodis;
				fs1.close();
				veiksmas.darom(zodis, HashIlgis);
				zodis.clear();

				fs1 >> zodis;
				fs1.close();
				veiksmas.darom(zodis, HashIlgis);
				zodis.clear();

			}
			else
			{
				cout << "failai nesugeneruoti. Generuojama...\n";
				generuojamF(automatizuotas);
			}
			fs1.close(); fs2.close();
		}
		else if (automatizuotas == 2)
		{
			ifstream fs1("Hasher1.txt");
			ifstream fs2("Hasher2.txt");

			if (fs1.good() && fs2.good())
			{
				fs1 >> zodis;
				veiksmas.darom(zodis, HashIlgis);
				zodis.clear();

				fs2 >> zodis;
				veiksmas.darom(zodis, HashIlgis);
				zodis.clear();
			}
			else
			{
				cout << "failai nesugeneruoti. Generuojama...\n";
				generuojamF(automatizuotas);
			}

			fs1.close(); fs2.close();
		}
		else if (automatizuotas == 3)
		{
				veiksmas.darom("a", HashIlgis);
				veiksmas.darom("b", HashIlgis);
		}
	}
}
void generuojamF(int generacija)
{
	srand(time(NULL));

	string zodis;
	int r;
	char c;
	if (generacija == 1)
	{
		for (int i = 0; i < 1000; i++)
		{
			r = rand() % 26;   // generate a random number
			c = 'a' + r;            // Convert to a character from a-z
			zodis += c;
		}
		ofstream fd("Hasher1.txt");
		fd << zodis;
		fd.close();

		for (int i = 0; i < 1000; i++)
		{
			r = rand() % 26;   // generate a random number
			c = 'a' + r;            // Convert to a character from a-z
			zodis += c;
		}
		fd.open("Hasher2.txt");
		fd << zodis;
		fd.close();

	}
	else if (generacija == 2)
	{
		for (int i = 0; i < 1000; i++)
		{
			r = rand() % 26;   // generate a random number
			c = 'a' + r;            // Convert to a character from a-z
			zodis += c;
		}
		ofstream fd("Hasher1.txt");
		fd << zodis;
		fd.close();

		zodis[999] = zodis[999] + 1;
		fd.open("Hasher2.txt");
		fd << zodis;
		fd.close();
	}
}