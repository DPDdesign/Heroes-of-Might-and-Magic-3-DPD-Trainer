// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
//  Creatures maxcap is 255, Only red player, only one map mode, the input file is generated manually.
// 0.20 update Read and write in one function
// 0.30 update Both players in one loop
// 0.31 update - code is more clear and everything is buffered in INPUT DATA to an internal buffer.
// 0.40 update - added every aspect of hero and offsets. Now only Hero type has to be set (line 86). Works for 1 hero only for now.
// 0.50 update - Working with classes, easy manipulation of input data, offsets, possibility of adding other heroes as well, no spells.
// 0.60 update - EVERYTHING WORKS FOR BOTH PLAYERS! 
// 0.65 update - code is now clear with notes for future devs

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
	gracz(int player_number, FILE* input_file) {									/// player_number starting from 0, input file
		getdata(player_number, input_file);											/// constructor - automatically get data from input file						
	}

	void getdata(int, FILE*);
	void write(FILE*);																

private:

	// Dedinition of locations in map
	int loc[2] = { 9887,9740 };
	int offset[12] = { 0,9,10,26,28,56,57,90,92,93,110,100 };						//	#DEFINE offsets - locations of each element in the map memory
	int jump[12] = { 1,2,2,4,4,2,2,1,1,1,1,1 };										//	#DEFINE jumps	- to overcome problem of overwriting, program is "jumping" over the map memory

	/// Definition of the input file
	FILE * input;
	int icount[12] = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1, 4, 72 };						/// Number of elements			(1 hero_name, 7 creatures' type, 7 creatures' amount, 72 spells)
	int	isize[12] =	 { 3, 3, 1, 3, 5,  3,  3, 3, 3, 3, 3,  1 };						/// Amount of signs per element	(127 heroes = 3 signs, maximum 30 000 creatures -  5 signs, 1 spell bool 0/1 )

	/// Definition for output file
	FILE* output;
	int ecount[12] = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1,4, 9};						/// Number of output elements	(the difference is in spells, since the output is 9 spell sums, not 72 bools)						
	int buffor[64][12];																/// output buffor 8 players * 8 heroes * 12 parameters per hero
	int hero_no;																	/// Number of hero
	
};

void gracz::getdata(int n, FILE* m)
{
	hero_no = n;																	/// Assigning a number for each hero (ordering class objets)
	input = m;																		/// Assigning the input file

	/// LOCAL VARIABLES 
	int herloc = n * 283;															/// Offset in input file reading
	char buffer[20];																/// Internal buffer for file reading (max 16 signs)
	int spell_value[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };							/// Spell values
	int spellbuffor[9] = { 0 };														/// Subbuffor - for counting the spell sum


	fseek(input, herloc, 0);														/// In input file, get to the location of hero_no
	for (int i = 0; i < 11; i++) {													
		for (int j = 0; j < icount[i]; j++) {
			fgets(buffer, isize[i] + 1, input);										/// Save isize of elements into temporary buffer
			buffor[i][j] = atoi(buffer);											/// Load data to object's buffor elements
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			fgets(buffer, 2, input);												/// Get data of spells
			spellbuffor[i] = spellbuffor[i] + atoi(buffer)* spell_value[j];			/// Calculate spell sum
		}
		buffor[11][i] = spellbuffor[i];												/// Load spell sum as the last element
	}

}

void gracz::write(FILE *output_file) {								
	
	output = output_file;															/// Asign output file
	int k = loc[hero_no];															/// 

	 for (int r = 0; r < 12; r++)
	{
		for (int i = 0; i < ecount[r]; i++)
		{
			int locm = k + offset[r] + i * jump[r];									/// point in the map memory to be overwritten
			stringstream sstream;
			sstream << std::hex << buffor[r][i];									/// change into hex
			string hexx = sstream.str();

			if (hexx.size() == 4) {													/// switch hex values (as the processor reats bytes backwards)

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

			else if (hexx.size() == 3)	{											/// For 3 byte numbers, write 1 , 2byte element, not to miss the '0' sign
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

/// READING DATA FROM INPUT FILE
	FILE* input;
	input = fopen("docore.txt", "r+");												/// Open input file

// #DEFINE PLAYERS
		gracz red(0,input);															/// Define first hero
		gracz blue(1,input);														/// Define second hero
	
	fclose(input);

/// GENERATING MAP FROM INTERNAL DATA
	FILE* output;
	output = fopen("mapka.dat", "rb+");												/// Open map file

// #GENERATE PLAYERS
		red.write(output);					
		blue.write(output);					

	fclose(output);
		
}
