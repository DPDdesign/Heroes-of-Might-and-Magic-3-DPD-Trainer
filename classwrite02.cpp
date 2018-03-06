// version still in development, does not provide all artifacts (warm machines, misc5), nor secondary skills.
// 0.2 Read and write in one function

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
	void zapisz(int[][50], int[], int[], int,int[], FILE*, bool);

private:
	int buffor[50][50], ecount[50], esize[50], loc[50], jump[50], number, row;

	
};

void test::zapisz(int values[][50], int counter[], int location[], int r, int jump[], FILE* output, bool test) {
	
	row = r;
	ecount[row] = counter[r];
	loc[row] = location[r];

	for (int i = 0; i < ecount[r]; i++)
	{
		buffor[row][i] = values[r][i];
		
		// BEZ MIESZANIA
		if		(test==0){
		fseek(output, loc[row] + i * jump[row], 0);
		fwrite(&buffor[row][i], 1, 1, output);
		}
		
		// MIESZANIE
		else if	(test==1){ 
			
			int locm = loc[row] + i* jump[row]; 	
			int buffm = buffor[row][i];
	
			stringstream sstream;
			sstream << std::hex << buffm;
			string hexx = sstream.str();
	
			if (hexx.size() == 4) {
				string hexxtemp;
				hexxtemp.append(hexx, 2, 2);
				hexx.erase(2, 2);
				int i_hex1 = std::stoi(hexxtemp, nullptr, 16);
				int i_hex2 = std::stoi(hexx, nullptr, 16);
	
				int buffer2[] = { i_hex1 };
				fseek(output, locm + 1, 0);
				fwrite(buffer2, 1, 1, output);
	
				int buffer3[] = { i_hex2 };
				fseek(output, locm, 0);
				fwrite(buffer3, 1, 1, output);
			}
		
			else{
				int buffer2[] = { buffm };
				fseek(output, locm, 0);
				fwrite(buffer2, 2, 1, output);
			}
		}
	}

}


int main() {
	
	//int buffor[50][50], ecount[50], esize[50], loc[50]

	int data[3][50] = { {1,2},{3,4,5},{6,7,8,9} };			//  dane
	int ecount[3] = { 2,3,4 }; 								// ile elementów pobrać
	int loc[3] = { 0,10,20 };								// gdzie zapisać pierwszy element
	int jump[3] = {3,2,1};									// co ile zapisać elementy
	
	
	
	FILE* output;
	output = fopen("tester.txt", "r+");
	test koksik;
	koksik.zapisz(data, ecount, loc, 0,jump,output,0);	// dane, ile, gdzie, rząd, co ile, dokąd, czy mieszać duże liczby
	koksik.zapisz(data, ecount, loc, 1,jump,output,0);
	koksik.zapisz(data, ecount, loc, 2,jump,output,0);
	
	return 0;
}

