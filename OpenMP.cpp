//Nathan Clark, CS 4170 Parallel Computing
//This Program is meant to compare the runtimes of
//a sequential program and parallel processes of differing amounts.
//This program will also run the parallel program on different
//sizes of matirces.

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]) {
    int row1, col1, col2 = 0;

        //determine what size the matrices will be with argument
    if (*argv[1] == 'T') {
            row1 = 5;
            col1 = 2;
            col2 = 3;
    }

    if (*argv[1] == 'A') {
        row1 = 50;            
        col1 = 20;
        col2 = 25;
    }

    if (*argv[1] == 'B') {
        row1 = 500;
        col1 = 200;
        col2 = 250;
    }

    if (*argv[1] == 'C') {
        row1 = 5000;
        col1 = 2000;
        col2 = 2500;
    }

    if (*argv[1] == 'D') {
        row1 = 50000;
        col1 = 20000;
        col2 = 25000;
    }
    else {
        return 1;
    }
    //determine the amount of threads used as an argument
    int threadNum = atoi(argv[2]);

    //allocating dynamic arrays
    double** A = new double* [row1];
    for (int i = 0; i < row1; ++i) {
        A[i] = new double[col1];
    }

    double** B = new double* [col1];
    for (int i = 0; i < col1; ++i) {
        B[i] = new double[col2];
    }

    double** Result = new double* [row1];
    for (int i = 0; i < row1; ++i) {
        Result[i] = new double[col2];
    }

    double start, end;
    //alocation of random variables into the matrices, and initializing result with 0.

    start = omp_get_wtime();

    #pragma omp parallel for num_threads(threadNum)
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1; ++j) {
                A[i][j] = (rand() % 1000000);
        }
    }

    #pragma omp parallel for num_threads(threadNum)
    for (int i = 0; i < col1; ++i) {
        for (int j = 0; j < col2; ++j) {
            B[i][j] = (rand() % 1000000);
            }
    }

    #pragma omp parallel for num_threads(threadNum)
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            Result[i][j] = 0;
        }
    }

        //If test case is called, it will output test output and do the calculation.
    if (*argv[1] == 'T') {
    for(int x = 0; x < row1; x++) {
        for (int y = 0; y < col2; ++y) {
            for (int i = 0; i < col1; ++i) {
                Result[x][y] += A[x][i] * B[i][y];
                cout << A[x][i] * B[i][y] << " + ";
            }
        cout << "= " << Result[x][y] << "\n";
        }
    printf("NewRow\n");
    }

    cout << "Result: \n\n\n";
        for (int i = 0; i < row1; ++i) {
            for (int j = 0; j < col2; ++j) {
                cout << Result[i][j] << " ";
                }
            cout << "\n\n";
            }
        }


    else {
    //Parallel computation of the matrix multiplication.
    #pragma omp parallel for num_threads(threadNum)
        for(int x = 0; x < row1; x++) {
            for (int y = 0; y < col2; ++y) {
                for (int i = 0; i < col1; ++i) {
                    Result[x][y] += A[x][i] * B[i][y];
                }
            }
        }
    }

    //print time
    end = omp_get_wtime();
    double time = double(end - start);
    printf("%f", time);
    printf("\n");

    //Deallocate memory
    for (int i = 0; i < row1; ++i) {
        delete[] A[i];
        delete[] Result[i];
    }
    delete[] A;
    delete[] B;
    delete[] Result;

    return 0;
}


