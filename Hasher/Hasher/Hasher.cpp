#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "Hashinimas.h"
using namespace std;

int HashIlgis=32; //turi buti dvigubai mazesnis uz Hash ilgi nes HexaDecimal yra sudarytas is 2 simboliu


int main()
{
	string zodis="a";
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
		int automatizuotas;
		cout << endl<<"1. 2 failai su 1000 skirtingai sugeneruotu simboliu kurie labai skiriasi\n2. 2 failai su 1000 skirtingai sugeneruotu simboliu, kurie beveik nesiskiria\n3. 2 failai kuriuose po 1 skirtinga simboli";
		cin >> automatizuotas;
		if (automatizuotas == 1)
		{
			for (int i = 0;i < 2;i++)
			{
				cout << "Iveskite failu pavadinimus:\nFailas 1: ";
				cin >> pavad1;
				cout << "Failas 2: ";
				cin >> pavad2;
				ifstream fs1(pavad1 + ".txt");
				fs1 >> zodis;
				fs1.close();
				veiksmas.darom(zodis,HashIlgis);

				ifstream fs2(pavad2 + ".txt");
				fs2 >> zodis;
				fs2.close();
				veiksmas.darom(zodis, HashIlgis);
			}
		}
		else if (automatizuotas == 2)
		{
			for (int i = 0;i < 2;i++)
			{
				cout << "Iveskite failu pavadinimus:\nFailas 1: ";
				cin >> pavad1;
				cout << "Failas 2: ";
				cin >> pavad2;
				ifstream fs1(pavad1 + ".txt");
				fs1 >> zodis;
				fs1.close();
				veiksmas.darom(zodis, HashIlgis);

				ifstream fs2(pavad2 + ".txt");
				fs2 >> zodis;
				fs2.close();
				veiksmas.darom(zodis, HashIlgis);
			}
		}
		else if (automatizuotas == 3)
		{
			for (int i = 0;i < 2;i++)
			{
				veiksmas.darom(zodis, HashIlgis);
				zodis = "b";
			}
		}
	}


}