// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
//  Creatures maxcap is 255, Only red player, only one map mode, the input file is generated manually.
// 0.31 update - code is more clear and everything is buffered in INPUT DATA to an internal buffer.
// 0.40 update - added every aspect of hero and offsets. Now only Hero type has to be set (line 86). Works for 1 hero only for now.

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


void stwory(int i, FILE* file, int loc) {


	 stringstream sstream;
	sstream << std::hex << i;
	string hexx = sstream.str();

	if (hexx.size() == 4) {
		string hexxtemp;
		hexxtemp.append(hexx, 2, 2);
		hexx.erase(2, 2);
		int i_hex1 = std::stoi(hexxtemp, nullptr, 16);
		int i_hex2 = std::stoi(hexx, nullptr, 16);

		int buffer2[] = { i_hex1 };
		fseek(file, loc + 1, 0);
		fwrite(buffer2, 1, 1, file);

		int buffer3[] = { i_hex2 };
		fseek(file, loc, 0);
		fwrite(buffer3, 1, 1, file);
	}
	else
	{
		int buffer2[] = { i };
		fseek(file, loc, 0);
		fwrite(buffer2, 2, 1, file);
	}

}

int main() {

	// #################### INPUT DATA ######################
	// Definition of input file structure

	char buffer[12];
	int input_data[50][50];														    //	|	0	|	 1		|		2		|	3		|	  4			|		 5		|		 6		|		7		|		8		|	  9		|	10		|	 11		|		12		|	
	int ecount[12] = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1, 72, 4 };				       ///	|#Ilosc	| 1 hero	|  8  sskill	| 8 sskil	|  7 creature	|  7 creature	| 16 artifact	| 16 artifact	| 2 Spell book	| 1 Misc5	| 1 Misc5	| 72 spells	|  4  pskill	|	
	int	esize[12] =  { 3, 2, 1, 3, 5,  3,  3, 3, 3, 3,  1, 3 };					 ///	|#Znaki	| 3 name	|  2  type		| 1 level	|  3 type		|  5 number		|  3 type		|  3 bool		| 3 bool		| 3 type	| 3 bool	|  1  bool	|  3  value		|			
																				 //		|#Suma	| 3			| 16			| 8 		| 21			| 35			| 48			| 48			| 6				| 3			| 3			| 72		| 12			|	
																				//#Total| 275	|

	// ################## PRE PROCESSOR ####################
	
	/// Generating internal buffer 
	FILE* input;
	input = fopen("Dane.dat", "r+");
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < ecount[i]; j++) {
			fgets(buffer, esize[i] + 1, input);
			input_data[i][j] = atoi(buffer);
			cout << input_data[i][j] << endl;
		}

	} fclose(input);

	/// Generating spell sub array
	int spell_value[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	int spell_sum[9] = { 0 };
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			spell_sum[i] = spell_sum[i] + input_data[3][j + i * 8] * spell_value[j];
		}
	}

	/// Generating adresses for output file
	int base[2] = { 9887,9740};									/// Blue, Red <- To be replaced with auto funciton
	long off[12] = { 0,9,10,26,28,56,57,90,92,93,100,111 };			/// DO NOT CHANGE
	int loc[12] = { 0 };

								///  =] you've got rick_rolled. Creating locations for each value.
		for (int i = 0; i < 12; i++) {
			loc[i] = base[0] + off[i];
		}
	


	// #################	EXECUTION #########################
	/// Writing to otput file

	FILE* output;
	output = fopen("tester", "r+");



		/// 0 Hero Name
		fseek(output, loc[0], 0);
		fwrite(&input_data[0][0], 1, 1, output);
		
		/// 1 Secondary Skill Type
		for (int i = 0; i < ecount[1]; i++)				{
			fseek(output,  loc[1]+2*i, 0)				;
			fwrite(&input_data[1][i],1,1,output)		;
		}
		
		/// 2  Secondary Skill Level
		for (int i = 0; i < ecount[2]; i++)				{
			fseek(output, loc[2] + 2 * i, 0)			;
			fwrite(&input_data[2][i], 1, 1, output)		;
		}

		/// 3, 4 Creature Type & Creature level
		for (int i = 0; i < ecount[3]; i++)				{
			stwory(input_data[3][i], output, loc[3] + i * 4)	;
			stwory(input_data[4][i], output, loc[4] + i * 4)	;
		}

		/// 5 Artifact Type
		for (int i = 0; i < ecount[5]; i++)				{
			fseek(output, loc[5] + 2 * i, 0)			;
			fwrite(&input_data[5][i], 1, 1, output)		;
		}

		/// 6 Artifact Bool
		for (int i = 0; i < ecount[6]; i++)				{
			fseek(output, loc[6] + 2 * i, 0)			;
			fwrite(&input_data[6][i], 1, 1, output)		;
		}

		/// 7 Spell book
		for (int i = 0; i < ecount[7]; i++)				{
			fseek(output, loc[7] + i, 0)				;
			fwrite(&input_data[7][i], 1, 1, output)		;
		}

		/// 8 Misc5 Type
		for (int i = 0; i < ecount[8]; i++)				{
			fseek(output, loc[8] +  i, 0)				;
			fwrite(&input_data[8][i], 1, 1, output)		;
		}

		/// 9 Misc5 Bool
		for (int i = 0; i < ecount[9]; i++)				{
			fseek(output, loc[9] + i, 0)				;
			fwrite(&input_data[9][i], 1, 1, output)		;
		}

		/// 10 Spells
		for (int i = 0; i < 9; i++)			{
			fseek(output, loc[10] + i, 0)				;
			fwrite(&spell_sum[i], 1, 1, output)			;	
		}

		/// 11 Primary Skills
		for (int i = 0; i < ecount[11]; i++) {
			fseek(output, loc[11] + i, 0);
			fwrite(&input_data[11][i], 1, 1, output);
		}


		fclose(output);
	
return 0;
}
