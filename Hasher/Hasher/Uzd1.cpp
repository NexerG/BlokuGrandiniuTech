#include "Uzd1.h"
const int Gen5 = 50000;

Uzd1::Uzd1()
{
	string zodis;
	Hashinimas veiksmas;
	string pavad1, pavad2;

	int startas;
	cout << "Pasirinkite kaip norite atlikti hash.\n1. Ivedimas ranka\n2. Is failo\n3. Konstitucija\n";
	cin >> startas;

	//ivedimas ranka
	if (startas == 1)
	{
		cin >> zodis;
		cout << veiksmas.darom(zodis, HashIlgis);
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
				cout << veiksmas.darom(zodis, HashIlgis);
				zodis.clear();

				fs1 >> zodis;
				fs1.close();
				cout << veiksmas.darom(zodis, HashIlgis);
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
				cout << veiksmas.darom(zodis, HashIlgis);
				zodis.clear();

				fs2 >> zodis;
				cout << veiksmas.darom(zodis, HashIlgis);
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
			cout << veiksmas.darom("a", HashIlgis);
			cout << veiksmas.darom("b", HashIlgis);
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
					eksportas = veiksmas.darom(zodis, HashIlgis) + "\n";
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
				float HashSkirtumas = 0, BitSkirtumas = 0;
				vector<string> Laikmena;

				//surinkimas
				while (fs >> dummy)
				{
					Laikmena.push_back(veiksmas.darom(dummy, HashIlgis));
				}
				fs.close();

				//tikrinimas hashu lygmeny bet geriau
				string Checkers = "0123456789abcdefghijklmnoprstuvzABCDEFGHIJKLMNOPRSTUVZ";
				vector<vector<int>> matrica(55,vector<int>(Gen5,-1));
				vector<string> Tikrinimas = Laikmena;
				cout<<matrica.size();
				auto start = high_resolution_clock::now();

				for (int i = 0; i < Tikrinimas.size(); i++)
					for (int k = 0; k < 64; k++)
						matrica[Checkers.find(Tikrinimas[i][k])][i]++;

				for (int i = 0; i < matrica.size(); i++)
				{
					for (int j = 0; j < matrica[i].size(); j++)
					{
						if (matrica[i][j] > 0)
							HashSkirtumas += matrica[i][j];
					}
				}
				auto end = high_resolution_clock::now();
				auto duration = duration_cast<milliseconds>(end - start);

				HashSkirtumas = HashSkirtumas / (Tikrinimas.size() * Tikrinimas[0].length());
				cout << "\nHashu panasumas, kai originalus stringai skiriasi labai mazai, yra: " << HashSkirtumas << "%\n";
				Tikrinimas.clear();

				string Pirmas, Antras;
				for (int i = 0; i < Laikmena.size(); i++)
				{
					for (int j = i + 1; j < Laikmena.size(); j++)
					{
						for (int k = 0; k < Laikmena[i].length(); k++)
						{
							Pirmas = bitset<8>(Laikmena[i][k]).to_string();
							Antras = bitset<8>(Laikmena[j][k]).to_string();
							for (int b = 0; b < 8; b++)
							{
								if (Pirmas[b] == Antras[b])
									BitSkirtumas++;
							}
						}
					}
				}
				BitSkirtumas = BitSkirtumas / (Laikmena.size() * Laikmena[0].length() * 8);
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
		for (int i = 1; i <= pow(2, 12); i = i * 2)
		{
			start = high_resolution_clock::now();
			fs.open("konstitucija.txt");
			for (int j = 0; j <= i; j++)
			{
				getline(fs, Linija);
				veiksmas.darom(Linija, HashIlgis);
			}
			end = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(end - start);
			cout << "Kad su'Hashinti " << i << " eiluciu uztruko: " << duration.count() << " ms\n";
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
		int RandIlgis, zdzIlgis = 250;

		for (int i = 0; i < zdzIlgis; i++)
		{
			r = rand() % 26;   // generate a random number
			c = 'a' + r;            // Convert to a character from a-z
			zodis += c;
		}
		for (int i = 0; i < Gen5; i++)
		{
			RandIlgis = rand() % zdzIlgis;
			r = rand() % 26;

			while ('a' + r == zodis[RandIlgis])
				r = rand() % 26;

			zodis[RandIlgis] = 'a' + r;
			fd << zodis << endl;
		}
		fd.close();
	}
	cout << "Sugeneruota.\n";
}
