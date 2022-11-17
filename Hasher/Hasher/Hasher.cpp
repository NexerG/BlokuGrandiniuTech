#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "Hashinimas.h"
#include <vector>
#include <chrono>
#include <math.h>
#include "Uzd1.h"
#include "Transactions.h"
#include "Vartotojas.h"
#include "Blokas.h"

using namespace std::chrono;

int main()
{
	//atkomentuoti jeigu norima perziureti pirma uzduoti
	//Uzd1 uzd;
	vector<Vartotojas> Vartotojai;
	vector<Transaction> Tranzakcijos;

	Hashinimas veiksmas;
	srand(time(NULL));
	int r;

	Vartotojas dummyV;
	for (int i = 0; i < 1000; i++)
	{
		dummyV.SetName("V" + to_string(i));
		dummyV.SetPubK(veiksmas.darom(dummyV.GetName(), 32));
		dummyV.SetBal(rand() % (i + 1 * 100));
		Vartotojai.push_back(dummyV);
	}

	Transaction dummyT;
	for (int i = 0; i < 10000; i++)
	{
		dummyT.SetSum(rand() % (i + 1 * 10));

		dummyT.SetPubKRec(Vartotojai[(rand() % Vartotojai.size())].GetPubK());
		dummyT.SetPubKSen(Vartotojai[(rand() % Vartotojai.size())].GetPubK());

		while (dummyT.GetPubKRec() == dummyT.GetPubKSender())
			dummyT.SetPubKSen(Vartotojai[(rand() % Vartotojai.size())].GetPubK());

		Tranzakcijos.push_back(dummyT);
	}


	//veliau turetu buti padaryta 1/ (miners)
	//veikia taip kad blokas turetu buti iskastas karta per 1 minute
	//todel sitas dalykas turi dinamiskai keistis kad on average 
	//atitiktu kriteriju
	int diff = 3;
	int laikas = 1;
	vector<Blokas> Blokai;
	while (Tranzakcijos.size() > 0)
	{
		vector<Transaction> LaikTrans;
		for (int i = 0; i < 100; i++)
		{
			r = rand() % Tranzakcijos.size();
			LaikTrans.push_back(Tranzakcijos[r]);
			Tranzakcijos.erase(Tranzakcijos.begin() + r);
		}

		Blokas Blck(LaikTrans, "1", diff, Vartotojai);

		if (Blck.GetHash() != "")
		{
			Blokai.push_back(Blck);
			LaikTrans.clear();
			diff++;
		}
		else
		{
			for (int i = 0; i < 100; i++)
			{
				Tranzakcijos.push_back(LaikTrans[i]);
			}
			LaikTrans.clear();
		}
	}
}