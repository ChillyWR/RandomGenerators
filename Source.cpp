#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Header.h"

int main() {
	unsigned int n;
	printf("%s", "Enter the generator number (from 1 to 10)\n");
	scanf_s("%u", &n);
	genSelection(&n);
	return 0;
}
void genSelection(unsigned int* n) {
	switch (*n)
	{
	case 1: {
		int x = 13;
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator1(&x, &result);
			distributor(result, evenLimits);
		}
		displayHistogram(operAmount, evenLimits); break;
	}
	case 2: {
		int x = 13;
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator2(&x, &result);
			distributor(result, evenLimits);
		}
		displayHistogram(operAmount, evenLimits); break;
	}
	case 3: {
		long long f0 = 0;
		long long f1 = 1;                                             //m = ?
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator3(&f0, &f1, &result, i);
			distributor(result, evenLimits);
		}
		displayHistogram(operAmount, evenLimits); break;
	}
	case 4: {
		int x = 1;
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator4(&x, &result);
			distributor(result, evenLimits);
		}
		displayHistogram(operAmount, evenLimits); break;
	}
	case 5: {
		int x1 = 13, x2 = 13;
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator5(&x1, &x2, &result);
			distributor(result, evenLimits);
		}
		displayHistogram(operAmount, evenLimits); break;
	}
	case 6: {
		int x = 13;
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator6(&x, &result);
			distributor(result, normalLimits);
		}
		displayHistogram(operAmount, normalLimits); break;
	}
	case 7: {                                        //check
		int x1 = 13, x2 = 17;
		double result1, result2;
		const short m = 257;
		for (int i = 0; i < operAmount; i++) {
			generator7(&x1, &x2, &result1, &result2);
			distributor(result1, normalLimits);
			distributor(result2, normalLimits);
		}
		displayHistogram(operAmount, normalLimits); break;
	}
	case 8: {
		int x = 13;
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator8(&x, &result);
			distributor(result, normalLimits);
		}
		displayHistogram(operAmount, normalLimits); break;
	}
	case 9: {
		int x = 13;
		double result;
		for (int i = 0; i < operAmount; i++) {
			generator9(&x, &result);
			distributor(result, otherLimits);
		}
		displayHistogram(operAmount, otherLimits); break;
	}
	case 10: {
		int x = 13;
		double result;
		const short m = 257;
		for (int i = 0; i < operAmount; i++) {
			generator10(&x, &result);
			distributor(result, otherLimits);
		}
		displayHistogram(operAmount, otherLimits); break;
	}
	default: {
		printf("%s", "Wrong generator number\n");
	}
	}
}
void distributor(double x, double(&limits)[limAmount]) {
	for (int i = 0; i < limAmount; i++) {
		if (x > limits[i] && x < limits[i + 1]) {
			histogram[i].push_back(x);
		}
	}
}
void displayHistogram(int operAmount, double(&limits)[limAmount]) {
	double sum = 0;
	printf(" Interval      Frequency\n");
	for (int i = 0; i < sizeof(limits) / sizeof(limits[0]) - 1; i++) {
		printf("[%.1f, %.1f]        %.2f\n", limits[i], limits[i + 1], float(histogram[i].size()) / operAmount);
		sum += float(histogram[i].size()) / operAmount;
	}
	printf("%.4f", sum);
	clearHisogram();
}
void clearHisogram() {
	for (int i = 0; i < 10; i++) {
		histogram[i].clear();
	}
}
//METHODS OF GENERATING UNIFORMLY DISTRIBUTED NUMBERS
void generator1(int* x, double* result) {
	//Linear congruent method
	const short a = 1543;                //257 * 6 + 1
	const short ñ = 89;
	const short m = 257;
	*x = (a * (*x) + ñ) % m;
	//printf("1:    %d\n", *x);
	*result = double(*x) / m;
}
void generator2(int* x, double* result) {
	//Quadratic congruent method
	const short a = 1413;                //353 * 4 + 1
	const short ñ = 3541;
	const short d = 1059;                 //353 * 3?
	const short m = 353;
	*x = (d * (*x) * (*x) + a * (*x) + ñ) % m;
	//printf("2:    %d\n", *x);
	*result = double(*x) / m;
}
void generator3(long long* f0, long long* f1, double* result, int i) {
	//Fibonacci numbers
	const short m = 31;
	if (i % 2 == 0) {
		*f0 = (*f1 + *f0) % m;
		*result = double(*f0) / m;
	}
	else {
		*f1 = (*f1 + *f0) % m;
		*result = double(*f1) / m;
	}
}
void generator4(int* x, double* result) {
	//Inverse congruent sequence
	const short a = 131;
	const short ñ = 154;
	const short m = 256;
	*x = (a * reverseByCongr(*x, m) + ñ) % m;
	//printf("4:    %d\n", *x);
	*result = double(*x) / m;
}
int reverseByCongr(int x, const short m) {
	int k = 0;
	while (int(float(m * k + 1) / x) != (float(m * k + 1) / x))
		k++;
	return (m * k + 1) / x;
}
void generator5(int* x1, int* x2, double* result) {
	//Merge method
	int r;
	const short m = 373;
	generator2(x1, result);
	//printf("5.1:    %d\n", *x1);
	generator4(x2, result);
	//printf("5.2:    %d\n", *x1);
	r = *x1 - *x2;
	while (r < 0) r += m;
	r %= m;
	*result = double(r) / m;
	//printf("5:    %d\n", r);
}
//METHODS OF GENERATING NORMALLY DISTRIBUTED NUMBERS
void generator6(int* x, double* result) {
	//3 sigma rule
	//Using 12 random numbers
	double sum = 0;
	for (int i = 0; i < 12; i++) {
		generator1(x, result);
		sum += *result;
	}
	*result = sum - 6;
}
void generator7(int* x1, int* x2, double* result1, double* result2) {
	//Polar coordinate method
	double u1, u2, v1, v2, s = 1;
	while (s >= 1) {
		generator1(x1, &u1); generator1(x2, &u2);
		v1 = 2 * u1 - 1, v2 = 2 * u2 - 1;
		s = v1 * v1 + v2 * v2;
	}
	double t = sqrt(-2 * log(s) / s);
	*result1 = v1 * t, * result2 = v2 * t;
}
void generator8(int* x, double* result) {
	//The method of relations
	double u, v, r;
	bool a = false, b = true, c = false;
	generator1(x, &u); generator2(x, &v);
	while (!a || b || !c) {
		if (u != 0) {
			r = sqrt(8 / exp(1)) * (v - 0.5) / u;
			a = (r * r <= 5 - 4 * exp(0.25) * u);
			b = (r * r >= 4 * exp(-1.35) / u + 1.4);
			c = (r * r <= -4 * log(u));
			generator1(x, &u);
		}
		else {
			generator1(x, &u);
		}
	}
	*result = r;
	//printf("8:    %.4f\n", r);
}
//Methods of generating other distributions
void generator9(int* x, double* result) {
	//Logarithm method for generating an indicative distribution
	const int a = 50;
	double u;
	generator1(x, &u);
	*result = -a * log(u);
	//printf("9     %.4f\n", *result);
}
void generator10(int* x, double* result) {
	//Ahrens method for generating a gamma distribution of order a > 1
	const int a = 50;
	const int b = 49;   //a - 1
	double u, v, y, r = 0;
	bool boo = true;
	while (r <= 0 || boo) {
		generator1(x, &u); generator2(x, &v);
		y = tan(M_PI * u);
		r = sqrt(2 * a - 1) * y + b;
		boo = (v > (1 + y * y) * exp((b)*log(r / (b)) - sqrt(2 * a - 1) * y));
	}
	*result = r;
	//printf("%.4f\n", r);
}