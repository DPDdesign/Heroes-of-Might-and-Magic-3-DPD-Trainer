// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
// 0.2 Read and write in one function
// 0.3 Both players in one loop

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


class gracz {

public:
	gracz(int value[][50], FILE* file){    
	getdata(value, file);
	}
	
	
	void getdata(int a[][50], FILE* f)
	{
		output = f;
		for(int i=0; i<noe; i++){
			for(int j = 0; j<ecount[i];j++) {buffor[i][j] = a[i][j];}
		}
	}
	
	void zapisz(int,int);
	

private:
	
	int noe = 3;
	int ecount[3] = { 4,5,10 }; 								// ile elementów pobrać
	int loc[3] = { 0,10,20 };								// gdzie zapisać pierwszy element
	int jump[3] = {3,2,1};									// co ile zapisać elementy	
															// ile elementów
	int buffor[50][50], locm;
	FILE* output;

};

void gracz::zapisz(int r, int k) {
	

	for (int i = 0; i < ecount[r]; i++)
	{	
			
			locm = k + loc [r] + i*jump[r];
			stringstream sstream;
			sstream << std::hex << buffor[r][i];
			string hexx = sstream.str();
			
			if (hexx.size() == 4) {
				
				string hexxtemp;
				hexxtemp.append(hexx, 2, 2);
				hexx.erase(2, 2);
				int i_hex1 = std::stoi(hexxtemp, nullptr, 16);
				int i_hex2 = std::stoi(hexx, nullptr, 16);
	
				fseek(output, locm + 1, 0);
				fwrite(&i_hex1, 1, 1, output);
	
				fseek(output, locm, 0);
				fwrite(&i_hex2, 1, 1, output);
			}
		
			 else{ 
			
				fseek(output, locm, 0);
				fwrite(&buffor[r][i], 1, 1, output);
			}
		}
	}



int main() {
	
	int loc[2] = {0,50};
	int data1[3][50] = { {10,2,3,4},{32124,5,6,7,26985},{8,9,10,11,12,13,14,15,16,17} };	
	int data2[3][50] = { {11,3,5,6},{32125,6,7,8,26986},{9,10,11,12,13,14,15,16,17,18} };		

	FILE* output;
	output = fopen("tester.txt", "rb+");

	  
	gracz czerwony(data1, output);
	gracz niebieski(data2, output);
	
	for(int i = 0; i<3; i++)	{
		czerwony.zapisz(i,loc[0]);
		niebieski.zapisz(i,loc[1]);
}

}

