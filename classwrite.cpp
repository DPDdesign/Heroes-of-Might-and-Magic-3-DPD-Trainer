#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <stdio.h>
#include <sstream>
using namespace std;


class test {

public:
	void zapisz(int, int, FILE*);
	void getdata(int[][50], int[], int[], int, int);

private:
	int buffor[50][50], ecount[50], esize[50], loc[50], number;
	
};

void test::getdata(int a[][50], int b[], int d[], int n, int k) {
	

	ecount[k] = b[k];
	loc[k] = d[k];

	for (int i = 0; i < n; i++)
	{
		buffor[k][i] = a[k][i];
	}

}

void test::zapisz(int n, int jump, FILE* output) {

	for (int i = 0; i < ecount[n]; i++)
	{
		fseek(output, loc[n] + i * jump, 0);
		fwrite(&buffor[n][i], 1, 1, output);
	}
}



int main() {
	
	//int buffor[50][50], ecount[50], esize[50], loc[50]

	int data[3][50] = { {10,20},{1,2,3},{4,5,6} };
	int ecount[3] = { 2,3,3 };
	int loc[3] = { 1,2,3 };

	
	
	FILE* output;
	output = fopen("tester.dat", "r+");
	test koksik;
	koksik.getdata(data, ecount, loc, 3, 1);
	koksik.zapisz(1, 1, output);
	
	
	
	system("pause");
	return 0;
}



