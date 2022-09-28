// Hasher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <bitset>
#include <algorithm> 
using namespace std;

int main()
{
	string zodis;
	cin >> zodis;

	if (zodis.length() < 64)
	{
		//dametam iki 64
		for (size_t i = 64; i < zodis.length(); i++)
		{
			zodis[i - 64] = (int)zodis[i - 64] / (int)zodis[i];
		}
	}

	else if (zodis.length() > 64)
	{
		//sumazinam iki 64
		for (size_t i = 64; i < zodis.length(); i++)
		{
			zodis[i - 64] = (int)zodis[i - 64] / (int)zodis[i];
		}
	}
	string testas = "abcd";
	rotate(testas.begin(), testas.begin() + 7, testas.end());
	cout << testas;

	string bitai;
	for (size_t i = 0; i < zodis.size(); i++)
	{
		if (i % 2 == 0)
		{
			zodis[i] = (int)zodis[i];
		}
		string rotuojam = bitset<8>(zodis[i]).to_string();
		
		//rotuojam bitus
		if (i % 2 == 0)
			rotate(rotuojam.begin(), rotuojam.begin() + 7, rotuojam.end());
		else if (i % 3 == 0)
			rotate(rotuojam.begin(), rotuojam.begin() - 5, rotuojam.end());
		else if(i%2==1)
			rotate(rotuojam.begin(), rotuojam.begin() + 27, rotuojam.end());
		else
			rotate(rotuojam.begin(), rotuojam.begin() - 3, rotuojam.end());

		bitai += rotuojam + " ";
	}
	//bitai
	//cout << bitai;
}
