#pragma once
#include <vector>

const int genAmount = 10;
const int limAmount = 11;
const unsigned int operAmount = 100;
std::vector<double> histogram[10];
double evenLimits[11] = { 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1 };
double normalLimits[11] = { -3, -2.4, -1.8, -1.2, -0.6, 0, 0.6, 1.2, 1.8, 2.4, 3 };
double otherLimits[11] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

//function prototypes
void genSelection(unsigned int* n);
void distributor(double y, double(&limits)[limAmount]);
void displayHistogram(int operAmount, double(&limits)[limAmount]);
void clearHisogram();

void generator1(int* x, double* result);
void generator2(int* x, double* result);
void generator3(long long* f0, long long* f1, double* result, int i);
void generator4(int* x, double* result);
int reverseByCongr(int x, const short m);
void generator5(int* x1, int* x2, double* result);

void generator6(int* x, double* result);
void generator7(int* x1, int* x2, double* result1, double* result2);
void generator8(int* x, double* result);

void generator9(int* x, double* result);
void generator10(int* x, double* result);