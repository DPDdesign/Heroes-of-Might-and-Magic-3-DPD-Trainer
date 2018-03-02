// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
//  Creatures maxcap is 255, Only red player, only one map mode, the input file is generated manually.


#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//umiejki
int umiejki()
{ return 0; }

// stwory
int stwory_rodzaje(FILE *input,FILE *output, int loc) {
	char rodzaje[21]; // 7 pól * 3 wartości
	for (int i = 0; i < 7; i++) {
		fseek(input, i * 3, 0);
		fread(rodzaje, 1, 3, input);
		int j = atoi(rodzaje);
		fseek(output, loc + i * 4, 0);
		fwrite(&j, 1, 1, output);
	}
	return 0;
}   

int stwory_ilosci(FILE *input, FILE *output, int loc) {
	char ilosci[35];
	for (int i = 0; i < 7; i++) {
		fseek(input, 21+i * 5, 0);
		fread(ilosci, 1, 5, input);
		int k = atoi(ilosci);
		fseek(output, loc+i * 4, 0);
		fwrite(&k, 1, 1, output);
	}
	return 0;
} 

//artefakty
int artefakty_rodzaje(FILE *input, FILE *output, int loc)
{
	char artefakty[48];  // 16 artefaktow * 3 wartosci
	for (int i = 0; i < 16; i++) {
		fseek(input, 56 + i * 3, 0);
		fread(artefakty, 1, 3, input);
		int l = atoi(artefakty);
		fseek(output, loc + i * 2, 0);
		fwrite(&l, 1, 1, output);
	}
	return 0;
}

int artefakty_bool(FILE *input, FILE *output, int loc)
{
	char artefakty[48];  // 16 artefaktow * 3 wartosci
	for (int i = 0; i < 16; i++) {
		fseek(input, 104 + i * 3, 0);
		fread(artefakty, 1, 3, input);
		int l = atoi(artefakty);
		fseek(output, loc + i * 2, 0);
		fwrite(&l, 1, 1, output);
	}
	return 0;
}

//spelle 
int spelle (FILE *input, FILE *output, int loc) {
	
	char spelle[72];
	int value[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

	for (int i = 0; i < 9; i++) {
		int suma = 0;
		for (int j = 0; j < 8; j++)
		{
			fseek(input, 152 + 8*i + j, 0);   // 56 -> offset od stworów 8*i+j <-- kolejne pozycje w pliku.
			fread(spelle, 1, 1, input);
			int k = atoi(spelle);
			suma = suma + k * value[j];
		}
		fseek(output, loc + i, 0);
		fwrite(&suma, 1, 1, output);

	}
	return 0;
}

//staty
int staty(FILE *input, FILE *output, int loc)
{
	char staty[12];  // 4 staty * 3 wartosci
	for (int i = 0; i < 4; i++) {
		fseek(input, 224 + i * 3, 0);
		fread(staty, 1, 3, input);
		int l = atoi(staty);
		fseek(output, loc + i, 0);
		fwrite(&l, 1, 1, output);
	}
	return 0;
}

int main()
{

	
	FILE *filei;
	filei = fopen("Input.dat", "r+");
	FILE *fileo;
	fileo = fopen("Mapa.dat", "rb+");
	
	int loc_type = 74613; //lokalizacja rodzajow --- w przyszlosci automatycznie
	int loc_amount = 74615; 
	int loc_artefakty = 74643;
	int loc_spelle = 74687;
	int loc_staty = 74697;
	
	
	
	stwory_rodzaje(filei, fileo, loc_type);
	stwory_ilosci(filei, fileo, loc_amount);
	spelle(filei, fileo, loc_spelle);
	artefakty_rodzaje(filei, fileo, loc_artefakty);
	artefakty_bool(filei, fileo, loc_artefakty+1);
	staty(filei, fileo, loc_staty);

	fclose(filei);
	fclose(fileo);


	return 0;
}
