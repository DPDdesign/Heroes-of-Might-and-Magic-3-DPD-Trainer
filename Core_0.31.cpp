// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
//  Creatures maxcap is 255, Only red player, only one map mode, the input file is generated manually.
// 0.31 update - code is more clear and everything is buffered in INPUT DATA to an internal buffer.


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

/*  This needs to be solved, and then everything can be written in one class.
int hexy(int i) {
	
	stringstream sstream;
	sstream << std::hex << i;
	string hexx = sstream.str();
	string hex_temp;
	string hex_reversed;

		hex_temp.append(hexx, 2, 2);
		hex_temp.append(hexx, 0, 2);
		int k = stoi(hex_temp, nullptr, 16);
		return k;
}
*/

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
	
//////////////////////////////////////////////////////////////////////////////INPUT DATA///////////////////////////////////////////////////////////////////////////////////
	char buffer[6];
	int input_data[50][50];
	int esize[6] = { 3,5,3,3,1,3 };								// Znaki: 3 rodzaj jednostki, 5 ilosc jednostki, 3 rodzaj artefaktu, 1 bool spell
	int ecount[6] = { 7,7,16,16,72,4 };							// Ilosc: 7 stworow , 16 artefaktow, 72 czary, 4 statystyki
	
	FILE* input;
	input = fopen("Dane.dat", "r+");
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < ecount[i]; j++) {
			fgets(buffer, esize[i]+1, input);
			input_data[i][j] = atoi(buffer);
			cout << input_data[i][j] << endl;
		}
	} fclose(input);
///////////////////////////////////////////////////////////////////////////PRE PROCESSOR//////////////////////////////////////////////////////////////////////////////////

	int spell_value[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	int spell_sum[9] = {0};
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			spell_sum[i] = spell_sum[i] + input_data[3][j + i * 8] * spell_value[j];
		}
	}

	/////////////////////////////////////////////////////////////////////EXECUTION/////////////////////////////////////////////////////////////////////////////////////////

	FILE* output;
	output = fopen("Output.dat", "r+");

	//Jednostki
	for (int i = 0; i < 7; i++) {
		stwory(input_data[0][i], output, 2 + i * 4);
		stwory(input_data[1][i], output, 2 + i * 4);
	}
	
	// Artefakty
	for (int i = 0; i < 16; i++) {
		fseek(output, 40+i*2, 0);
		fwrite(&input_data[2][i], 1, 1, output);
		fseek(output, 41 + i * 2, 0);
		fwrite(&input_data[3][i], 1, 1, output);
	}

	//Spelle
	for (int i = 0; i < 9; i++){
		fseek(output, 70 + i, 0);
		fwrite(&spell_sum[i], 1, 1, output);
	}

	//Staty
	for (int i = 0; i < 4; i++) {
		fseek(output, 80 + i, 0);
		fwrite(&input_data[5][i], 1, 1, output);
	}
	fclose(output);

	return 0;
}
