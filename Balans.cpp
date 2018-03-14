// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class stwor
{
public:
	stwor(int, int, int, int, int, string);
	void walka(int, int, int, int);
	void print();
	void wypisz(int );
	static int staty[200][4];
private:
	string name;
};

int stwor::staty[200][4] = { 0 };

stwor::stwor(int i, int attack, int deffence, int damage, int HealthPoints, string nazwa)
{
	name = nazwa;
	staty[i][0] = attack;
	staty[i][1] = deffence;
	staty[i][2] = damage;
	staty[i][3] = HealthPoints;
	
	wypisz(i);
}

void stwor::wypisz(int i) {
	int k = i;

	cout <<"Stwor: " << name <<endl;
	cout <<"Atak: " << staty[k][0] << endl;
	cout << "Obrona: " << staty[k][1] << endl;
	cout << "Obrazenia: " << staty[k][2] << endl;
	cout << "Zycie: " << staty[k][3] << endl << endl;
}
void stwor::walka(int id, int di, int n, int m)
{
	int dd; 
	int i = id;
	int j = di;

	int att1 = staty[i][0];
	int def1 = staty[i][1];
	int dmg1 = staty[i][2];
	int hps1 = staty[i][3];
	int amt1 = n;

	int att2 = staty[j][0];
	int def2 = staty[j][1];
	int dmg2 = staty[j][2];
	int hps2 = staty[j][3];
	int amt2 = m;

	if (att1 > att2)
	{
		double i1 = 0.05 * (att1 - def2);
			dd = n * dmg1 * (1 + i1);

	}
	else
	{
		double r1 = 0.025 * (def2 - att1);
			dd = n * dmg1 * (1 - r1);
	}
	double killed = dd / hps2;
} 

int main()
{
	stwor peasant(1, 1, 1, 1, 1, "Peasant");
	stwor angel(2, 20, 20, 50, 200, "Archangel");
	
}

