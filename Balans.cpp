// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

class stwor
{
public:
	stwor(int, int, int, int, int, string);
	void walka(int, int, int, int);
	void print();
	void wypisz(int);
	static int staty[200][5];
	static string name[200];
private:
	
	int ID;
};

int stwor::staty[200][5] = { 0 };
string stwor::name[200]={"0"};

stwor::stwor(int ID, int attack, int deffence, int damage, int HealthPoints, string nazwa)
{
	int i = ID;
	name[i] = nazwa;
	staty[i][0] = ID;
	staty[i][1] = attack;
	staty[i][2] = deffence;
	staty[i][3] = damage;
	staty[i][4] = HealthPoints;
	
	wypisz(i);
}

void stwor::wypisz(int i) {
	
	cout <<"Stwor: " << name[i] <<endl;
	cout <<"Atak: " << staty[i][1] << endl;
	cout << "Obrona: " << staty[i][2] << endl;
	cout << "Obrazenia: " << staty[i][3] << endl;
	cout << "Zycie: " << staty[i][4] << endl << endl;
}
void stwor::walka(int id, int di, int n, int m)
{
	int dd; 
	int i = id;
	int j = di;
	
	bool c1 = 1;
	int att1 = staty[i][1];
	int def1 = staty[i][2];
	int dmg1 = staty[i][3];
	int hp1s = staty[i][4];
	int amt1 = n;

	bool c2 = 1;
	int att2 = staty[j][1];
	int def2 = staty[j][2];
	int dmg2 = staty[j][3];
	int hp2s = staty[j][4];
	int amt2 = m;

double killed;
cout  << n << " " << name[i] << " Attacks " << m << " " << name[j] <<endl <<endl;
int hp1 = hp1s * n;
int hp2 = hp2s * m; 
int hp1c = hp1s; int hp2c=hp2s;

while ( m > 0)	{	

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
		
		
		cout << n <<" " <<name[i]<<" deals: "<< dd << " to " <<name[j]<<endl;
	
		if (dd > hp2s){
			killed = dd/hp2s;
			hp2c -= dd%hp2s;
		}
		
		else{
			
			if (dd > hp2c){
			killed = 1; }
			
			else{hp2c -= hp2s - dd; killed = 0; 	}
		}
		
		m-=killed;	
		cout << " killed " << killed << endl << " hp left " << hp2c << endl;
		
		
	/*	
			if (att2 > att1)
		{
			double i1 = 0.05 * (att2 - def1);
				dd = n * dmg1 * (1 + i1);
		}
		else
		{
			double r1 = 0.025 * (def1 - att2);
				dd = n * dmg1 * (1 - r1);
		}
		killed = dd / hps1;
		cout << m <<" " <<name[j]<<" deals: "<< dd << " to " <<name[i]<<endl<<endl;
		n -= killed;
	*/	
		
		
	}



} 

int main()
{
	stwor troglo(0,4,3,2,5, "Troglo");
	stwor peasant(1, 1, 1, 1, 1, "Peasant");
	stwor angel(2, 20, 20, 50, 200, "Archangel");
	troglo.walka(0,2,100,3);
	
	

}
