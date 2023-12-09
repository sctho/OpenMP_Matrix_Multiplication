//Nathan Clark, CS 4170 Parallel Computing
//This Program is meant to compare the runtimes of
//a sequential program and parallel processes of differing amounts.
//This program will also run the parallel program on different
//sizes of matirces.

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
	int row1 = 5000;
	int col1 = 2000;
	int col2 = 2500;

	if (*argv[1] == 'T') {
        row1 = 5;
        col1 = 2;
        col2 = 3;
    	}	

	if (argv[1] == "A") {
		int row1 = 50;
		int col1 = 20;
		int col2 = 25;
	}

	if (argv[1] == "B") {
		int row1 = 500;
		int col1 = 200;
		int col2 = 250;
	}

	if (argv[1] == "C") {
		int row1 = 5000;
		int col1 = 2000;
		int col2 = 2500;
	}

	if (argv[1] == "D") {
		int row1 = 50000;
		int col1 = 20000;
		int col2 = 25000;
	}

	vector<vector<double>> A(row1, vector<double>(col1));
	vector<vector<double>> B(col1, vector<double>(col2));
	vector<vector<double>> Result(row1, vector<double>(col2));


	clock_t start, end;

	start = clock();
	for (int i = 0; i < row1; ++i) {
		for (int j = 0; j < col1; ++j) {  
			A[i][j] = (rand()%1000000);
		}
	}
	for (int i = 0; i < col1; ++i) {
		for (int j = 0; j < col2; ++j) {
			B[i][j] = (rand()%1000000);
		}
	}

	for (int i = 0; i < row1; ++i) {
		for (int j = 0; j < col2; ++j) {
			Result[i][j] = 0;	
		}	
	}

	for (int x = 0; x < row1; ++x) {
		for (int y = 0; y < col2; ++y) {
			for (int i = 0; i < col1; i++) {
				Result[x][y] += A[x][i] * B[i][y];
			}		
		}	
	}

	
	end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC;
	time = time * 1000;
	std::cout << time;
	std::cout << "\n";
}

