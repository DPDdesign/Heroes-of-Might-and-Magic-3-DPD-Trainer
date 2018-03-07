// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
//  Creatures maxcap is 255, Only red player, only one map mode, the input file is generated manually.
// 0.2 Read and write in one function
// 0.3 Both players in one loop
// 0.31 update - code is more clear and everything is buffered in INPUT DATA to an internal buffer.
// 0.40 update - added every aspect of hero and offsets. Now only Hero type has to be set (line 86). Works for 1 hero only for now.
// 0.50 update - Working with classes, easy manipulation of input data, offsets, possibility of adding other heroes as well, no spells.
// 0.60 update - EVERYTHING WORKS FOR BOTH PLAYERS! 
#define _CRT_SECURE_NO_WARNINGS
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
	gracz(int k, FILE* f) {
		getdata(k, f);
	}

	void zapisz();


	void getdata(int n, FILE* k)
	{
		int herloc = n * 283;
		hn = n;
		output = k;
		char buffer[60];
		int spell_value[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

		FILE* input;
		input = fopen("docore.txt", "r+");
		fseek(input, herloc, 0);
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < icount[i]; j++) {
				fgets(buffer, isize[i] + 1, input);
				buffor[i][j] = atoi(buffer);
			}	
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
				fgets(buffer, 2, input);
				spellbuffer[i] = spellbuffer[i] + atoi(buffer)* spell_value[j];
			}
			buffor[11][i] = spellbuffer[i];
			cout << "Spell buffer" << buffor[11][i] << endl;;
		}

		fclose(input);
	}



private:

	FILE * input;
	int icount[12] = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1, 4, 72 }; 
	int	isize[12] =	 { 3, 3, 1, 3, 5,  3,  3, 3, 3, 3, 3,  1 };

	FILE* output;
	int ecount[12] = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1,4,9};								
	int offset[12] = { 0,9,10,26,28,56,57,90,92,93,110,100};
	int jump[12] = { 1,2,2,4,4,2,2,1,1,1,1,1 };																	
																							
	int buffor[50][50], locm;
	int spellbuffer[9] = { 0 };
	int loc[2] = { 9887,9740 };
	int hn;

	
	
};

void gracz::zapisz() {

	int k = loc[hn];

	 for (int r = 0; r < 12; r++)
	{
		for (int i = 0; i < ecount[r]; i++)
		{

			locm = k + offset[r] + i * jump[r];
			stringstream sstream;
			sstream << std::hex << buffor[r][i];
			string hexx = sstream.str();

			if (hexx.size() == 4) {

				string hexxtemp;
				hexxtemp.append(hexx, 2, 2);
				hexx.erase(2, 2);
				int i_hex1 = std::stoi(hexxtemp, nullptr, 16);
				int i_hex2 = std::stoi(hexx, nullptr, 16);

				fseek(output, locm, 0);
				fwrite(&i_hex1, 1, 1, output);

				fseek(output, locm + 1, 0);
				fwrite(&i_hex2, 1, 1, output);
			}

			else if (hexx.size() == 3)
			{

				fseek(output, locm, 0);
				fwrite(&buffor[r][i], 2, 1, output);
			}

			else {

				fseek(output, locm, 0);
				fwrite(&buffor[r][i], 1, 1, output);
			}
		}
	}
}


int main() {

	

	FILE* output;
	output = fopen("mapka.dat", "rb+");
	
	gracz czerwony(0,output);
	gracz niebieski(1, output);

	
		czerwony.zapisz();
		niebieski.zapisz();

		


	system("pause");
}
