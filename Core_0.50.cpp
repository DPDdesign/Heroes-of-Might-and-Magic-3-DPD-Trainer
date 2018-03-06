// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
//  Creatures maxcap is 255, Only red player, only one map mode, the input file is generated manually.
// 0.2 Read and write in one function
// 0.3 Both players in one loop
// 0.31 update - code is more clear and everything is buffered in INPUT DATA to an internal buffer.
// 0.40 update - added every aspect of hero and offsets. Now only Hero type has to be set (line 86). Works for 1 hero only for now.
// 0.50 update - Working with classes, easy manipulation of input data, offsets, possibility of adding other heroes as well, no spells.


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
	gracz(FILE* f) {getdata(f);}

	void getdata(FILE* k)
	{
		output = k;
		char buffer[60];

		FILE* input;
		input = fopen("Dane.dat", "r+");
		
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < icount[i]; j++) {
				fgets(buffer, isize[i] + 1, input);
				buffor[i][j] = atoi(buffer);
			}
		}
		
		/* THIS IS SPELL SECTION TO BE IMPLEMENTED SOON
		int spell_value[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
			buffor[12][i] = spell_sum[i] + input_data[3][j + i * 8] * spell_value[j];
			}
		} */	
		
		fclose(input);
	}
	
	void zapisz(int, int);
	
private:
	FILE * input;
	int icount[11] = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1, 4 };
	int	isize[11] = { 3, 2, 1, 3, 5,  3,  3, 3, 3, 3,  3 };

	FILE* output;
	int noe = 11;
	int ecount[11] = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1,4};		// will be ecount[12] as soon as spells will be added						
	int offset[11] = { 0,9,10,26,28,56,57,90,92,93,110};		// offsets in memory of the map (not sure if constant for all players)
	int jump[11] = { 1,2,2,4,4,2,2,1,1,1,1 };			// steps in which memory is written 															
																								
	int buffor[50][50], locm;	
};

void gracz::zapisz(int r, int k) {

	for (int i = 0; i < ecount[r]; i++)				// all values are exchanged into hex, does not cover 3char hex yet
	{

		locm = k + offset[r] + i * jump[r];			// where the value is placed
		
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

		else {
			fseek(output, locm, 0);
			fwrite(&buffor[r][i], 1, 1, output);
		}
	}
}





int main() {

	int loc[2] = { 9887,50 };					// location of red player, blue player (useless now)
	
	FILE* output;
	output = fopen("mapka.dat", "rb+");
	gracz czerwony(output);

	for (int i = 0; i<11; i++) {					// without spells there is 11 things to be written into memory
	czerwony.zapisz(i, loc[0]);					// each thing is held in buffor[r] , r standing for "row"
	}								// the maximum number of cointainer is 16 artifacts
									// thus buffor is set to buffor[12][16] (11 w/o spells)
}
