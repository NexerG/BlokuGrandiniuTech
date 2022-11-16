#pragma once

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
#include "sha256.h"

using namespace std;
using namespace std::chrono;

class Uzd1
{
	const int HashIlgis = 32; //turi buti dvigubai mazesnis uz Hash ilgi nes HexaDecimal yra sudarytas is 2 simboliu
	const int punktas4 = 100000;

	void generuojamF(int generacija);

public:
	Uzd1();
};

