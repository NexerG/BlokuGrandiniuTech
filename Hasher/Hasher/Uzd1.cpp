#include "Uzd1.h"

const int Gen5 = 100000;

Uzd1::Uzd1()
{
	string zodis;
	string pavad1, pavad2;

	int startas;
	cout << "Pasirinkite kaip norite atlikti hash.\n1. Ivedimas ranka\n2. Is failo\n3. Konstitucija\n";
	cin >> startas;

	//ivedimas ranka
	if (startas == 1)
	{
		cin >> zodis;
		cout << Sha256(zodis);
	}

	//duomenys is failu (be konstitucijos)
	else if (startas == 2)
	{
		int generacija;
		int automatizuotas;
		//string zodis1, zodis2;

		cout << "\n1. 2 failai su 1000 skirtingai sugeneruotu simboliu kurie labai skiriasi\n";
		cout << "2. 2 failai su 1000 skirtingai sugeneruotu simboliu, kurie beveik nesiskiria\n";
		cout << "3. 2 failai kuriuose po 1 skirtinga simboli\n";
		cout << "4. Tikrinti faila su " << punktas4 << " stringu (eiluciu), kuriu ilgiai po 1000\n";
		cout << "5. Tikrinti hashu ir ju bitu skirtinguma\n";
		cin >> automatizuotas;

		cout << "ar generuoti failus? 1- Taip. 2- Ne.\n";
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
				cout << Sha256(zodis);
				zodis.clear();

				fs1 >> zodis;
				fs1.close();
				cout << Sha256(zodis);
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
				cout << Sha256(zodis);
				zodis.clear();

				fs2 >> zodis;
				cout << Sha256(zodis);
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
			cout << Sha256("a");
			cout << Sha256("b");
		}

		else if (automatizuotas == 4)
		{
			ifstream fs1("Hasher1.txt");
			string eksportas;

			if (fs1.good())
			{
				ofstream fd("25000.txt");
				for (int i = 0; i < punktas4; i++)
				{
					fs1 >> zodis;
					eksportas = Sha256(zodis) + "\n";
					fd << eksportas;

					eksportas.clear();
					zodis.clear();
				}
				fd.close();
			}
			else
			{
				cout << "failai nesugeneruoti. Generuojama...\n";
				generuojamF(automatizuotas);
			}

			ifstream fs2("25000.txt");
			vector<string> tikrinam;
			string dummy;
			int kartojames = 0;

			for (int i = 0; i < punktas4; i++)
			{
				fs2 >> dummy;
				tikrinam.push_back(dummy);
				dummy.clear();
			}
			fs2.close();

			for (int i = 0; i < punktas4; i++)
			{
				for (int j = i + 1; j < punktas4; j++)
				{
					if (tikrinam[j] == tikrinam[i] && i != j)
						kartojames++;
				}
			}
			cout << kartojames << " kartu kartojasi\n";
		}

		else if (automatizuotas == 5)
		{
			ifstream fs("Hasher1.txt");
			if (fs.good())
			{
				//apsirasom kintamuosius
				string dummy;
				float HashSkirtumas = 0.f, BitSkirtumas = 0.f;
				vector<string> Laikmena;

				//surinkimas
				while (fs >> dummy)
				{
					Laikmena.push_back(Sha256(dummy));
				}
				fs.close();

				ofstream fd("testas.txt");
				for (int i = 0; i < Laikmena.size(); i++)
				{
					fd << Laikmena[i] << endl;
				}

				//tikrinimas hashu lygmeny bet geriau
				string Checkers = "0123456789abcdef";
				vector<vector<int>> matrica(64,vector<int>(16,-1));
				vector<string> Tikrinimas = Laikmena;
				//auto start = high_resolution_clock::now();
				int did = 0;

				for (int i = 0; i < Tikrinimas.size(); i++)
					for (int k = 0; k < 64; k++)
						matrica[k][Checkers.find(Tikrinimas[i][k])]++;

				for (int i = 0; i < matrica.size(); i++)
				{
					for (int j = 0; j < matrica[i].size(); j++)
					{
						if (matrica[i][j] > did)
							did = matrica[i][j];
					}
				}

				//auto end = high_resolution_clock::now();
				//auto duration = duration_cast<milliseconds>(end - start);
				HashSkirtumas = (float)did/(float)Gen5*100;
				cout << "\nHashu panasumas yra: " << HashSkirtumas << "%\n";
				Tikrinimas.clear();

				vector<vector<int>> MatBit(2, vector<int>(64 * 8, -1));
				string Pirmas, Antras="01";
				for (int i = 0; i < Laikmena.size(); i++)
				{
					for (int k = 0; k < 64; k++)
					{
						Pirmas = bitset<8>(Laikmena[i][k]).to_string();
						for (int b = 0; b < 8; b++)
						{
							if (int(Pirmas[b])-48 == 0)
								MatBit[0][b + k * 8]++;
							else MatBit[1][b + k * 8]++;
						}
					}
				}
				for (int i = 0; i < MatBit.size(); i++)
				{
					for (int j = 0; j < MatBit[i].size(); j++)
					{
						if (MatBit[i][j] > 0)
							BitSkirtumas += MatBit[i][j];
					}
				}

				BitSkirtumas = BitSkirtumas / (Laikmena.size() * 64 * 8) / 2 * 100;
				Laikmena.clear();
				cout << "\nHashu panasumas, bitu lygmenyje, yra: " << BitSkirtumas << "%\n";
			}

			//tikrinimas bitu lygmeny

			else
			{
				cout << "failai nesugeneruoti. Generuojama...\n";
				generuojamF(automatizuotas);
			}
		}
	}

	//konstitucija
	else if (startas == 3)
	{
		//konstitucija
		ifstream fs;
		string Linija;
		auto start = high_resolution_clock::now();
		auto end = high_resolution_clock::now();
		float Senas,Delta=0;
		for (int i = 1; i <= pow(2, 12); i = i * 2)
		{
			start = high_resolution_clock::now();
			fs.open("konstitucija.txt");
			for (int j = 0; j <= i; j++)
			{
				getline(fs, Linija);
				Sha256(Linija);
			}
			end = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(end - start);
			if (i>1)
			{
				Delta = duration.count() - Senas;
			}
			Senas = duration.count();
			cout << "Kad su'Hashinti " << i << " eiluciu uztruko: " << duration.count() << " ms " << "ir skirtumas nuo seno yra: " << Delta << " ms\n";
			fs.close();
		}
	}

}

void Uzd1::generuojamF(int generacija)
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
	else if (generacija == 4)
	{
		ofstream fd("Hasher1.txt");
		for (int j = 0; j < punktas4; j++)
		{
			for (int i = 0; i < 1000; i++)
			{
				r = rand() % 26;   // generate a random number
				c = 'a' + r;       // Convert to a character from a-z
				zodis += c;
			}
			fd << zodis << endl;
			zodis.clear();
		}
		fd.close();
	}

	else if (generacija == 5)
	{
		ofstream fd("Hasher1.txt");
		int RandIlgis, zdzIlgis = 100;
		for (int j = 0; j < Gen5; j++)
		{
			for (int i = 0; i < zdzIlgis; i++)
			{
				r = rand() % 26;   // generate a random number
				c = 'a' + r;            // Convert to a character from a-z
				zodis += c;
			}
			fd << zodis << endl;
			zodis = "";
		}
		//for (int i = 0; i < Gen5; i++)
		//{
		//	RandIlgis = rand() % zdzIlgis;
		//	r = rand() % 26;

		//	while ('a' + r == zodis[RandIlgis])
		//		r = rand() % 26;

		//	zodis[RandIlgis] = 'a' + r;
		//	fd << zodis << endl;
		//}
		fd.close();
	}
	cout << "Sugeneruota.\n";
}