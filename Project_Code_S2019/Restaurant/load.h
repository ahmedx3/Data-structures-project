#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class load
{
	int sn;
	int sf;
	int sv;
	int n[4];
	int f[4];
	int v[4];
	int autoS;
	int m;
public:
	load(string path);
	void printInfo();
	~load();
};

