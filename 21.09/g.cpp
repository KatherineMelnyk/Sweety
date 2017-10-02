#include <iostream>
#include <string>
#include <cmath>
#define M_E 2.7182818284
#define M_PI 3.14159265358979323846
static long long m = 10000009;

using namespace std;

double line_generator() {
	static int x = 0;
	static int a = 2;
	static int c = 23;
	x = (a*x + c) % m;
	return double(x) / (m - 1);
}

double quad_generator() {
	static long long x = 0;
	static long long a = 6;
	static long long d = 1;
	static long long c = 29;
	x = (d*x*x + a*x + c) % m;
	return double(x) / (m - 1);
}

double fib_generator() {
	static long long f1 = 1;
	static long long f2 = 1;
	static long long f3 = 2;
	f3 = (f1 + f2) % m;
	f1 = f2; f2 = f3;
	return double(f3) / (m - 1);
}

long long inverse(long long b) {
	long long ex = m - 2;
	if (b == 1)return 1;
	long long r = 1;
	while (ex) {
		if (ex & 1)r = (r * b) % m;
		ex = ex >> 1;
		b = (b * b) % m;
	}
	return r;
}

double inver_generator() {
	static long long x = 122;
	static long long a = 13;
	static long long c = 14;
	x = (a*inverse(x) + c) % m;
	return double(x) / m;
}

double union_generator() {
	static int step = 3;
	static long long m1 = 10000009;
	static long long m2 = 78574;
	static long long X[4] = { 3, 5, 8 };
	static long long Y[4] = { 2, 6, 4 };
	static long long A[3] = { 0, 13, 7 };
	static long long B[3] = { 1, 6, 4 };
	X[step] = (A[0] * X[(step + 1) % 4] + A[1] * X[(step + 2) % 4] + A[2] * X[(step + 3) % 4]) % m1;
	Y[step] = (B[0] * Y[(step + 1) % 4] + B[1] * Y[(step + 2) % 4] + B[2] * Y[(step + 3) % 4]) % m2;
	long long Z = abs(X[step] - Y[step]) % m1;
	step = (step + 1) % 4;
	return double(Z) / (m1);
}

double rule3_generator() {
	double next;
	static int m = 0;
	static int s = 1;
	double A[12];
	double sum = 0;
	for (int q = 0; q < 12; ++q)
	{
		A[q] = line_generator();
		sum = sum + A[q];
	}
	next = m + s*(sum - 6);
	return next;
}

bool ready = false;
double pol;
double polar_genrator() {
	if (ready == false) {
		double V1, V2, S, X1, X2;
		do {
			V1 = 2 * line_generator() - 1;
			V2 = 2 * line_generator() - 1;
			S = pow(V1, 2) + pow(V1, 2);
		} while (S >= 1);
		X1 = V1*sqrt(-2 * log(S) / S);
		X2 = V2*sqrt(-2 * log(S) / S);
		pol = X2;
		ready = true;
		return X1;
	}
	else
	{
		ready = false;
		return pol;
	}
}

double method_generator() {
	double  U, V, X;
	do {
		U = quad_generator();
		V = union_generator();
		X = sqrt(8.0 / M_E)*(V - 0.5) / U;
		if (X*X <= 5 - 4 * pow(M_E, 0.25)*U)
			return X;
	} while (pow(X, 2) > -4 * log(U));
	return X;
}

double log_generator() {
	double U, X;
	static const int mu = 13;
	do
	{
		U = union_generator();
	} while (U == 0);
	X = -mu*log(U);
	return X;
}

double arens_generator() {
	double U, Y, X, V;
	int  a = 1;
	do {
		U = fib_generator();
		Y = tan(M_PI*U);
		X = exp(2 * a - 1)*Y + a - 1;
		V = fib_generator();
	} while (X <= 0 && (V > (1 + pow(Y, 2))*exp((a - 1)*log(X / a - 1) - sqrt(2 * a - 1)*Y)));
	return X;
}

void firstHistogram(double(*generator)()) {
	int result[10] = { 0 };
	int num = 100000;
	for (int i = 0; i < num; i++) {
		result[int(generator() * 10)]++;
	}
	cout << "Interval\tStatistic" << endl;
	for (int i = 0; i < 10; i++)
		printf("[%1.1f .. %1.1f]\t%.4f\n", 0.1*i, 0.1*i + 0.1, double(result[i]) / num);
}

void secondHistogram(double(*generator)()) {
	int result[6] = { 0 };
	int num = 100000;
	int t = 0;
	for (int i = 0; i < num; i++) {
		t = int(generator() + 3);
		if (t<6 && t >= 0)
			result[t]++;
	}
	cout << "Interval\tStatistic" << endl;
	for (int i = 0; i < 6; i++)
		printf("[%1.1f .. %1.1f]\t%.4f\n", -3.0 + i, -3.0 + (i + 1), double(result[i]) / num);
}

void thirdHistogram(double(*generator)()) {
int result[10] = { 0 };
int num = 100000;
int m = 0; 
for (int i = 0; i < num; i++) {
	m = int(generator()/10);
	if (m<10 && m>=0)
     result[m]++;
}
cout << "Interval\tStatistic" << endl;
for (int i = 0; i < 10; i++)
printf("[%1.1f .. %1.1f]\t%.4f\n", i * 10.0, i * 10.0 + 10.0, double(result[i]) / num);
}

int main() {	
	int n;
	string a = "1.The linear congruent method \n";
	string b = "2.The quadratic congruent method \n";
	string c = "3.The Fibonacci numbers \n";
	string d = "4.The inverse congruent sequence \n";
	string f = "5.The method of unification \n";
	string j = "6.The Rule 3 sigma \n";
	string h = "7.The polar coordinate method \n";
	string k = "8.The method of correlations \n";
	string l = "9.Logarithm method for generating an indicative distribution \n";
	string g = "10.The Arens method for generating gamma-distribution order \n";
	string q = "Good Day!Enter your value from 1 to 10: \n";
	cout << q;
	string menu = a + b + c + d + f + j + h + k + l + g;
	cout << menu;
	while (cin >> n) {
		switch (n) {
		case 1: cout << a << endl;
			firstHistogram(&line_generator);
			break;
		case 2:	cout << b << endl;
			firstHistogram(&quad_generator);
			break;
		case 3:	cout << c << endl;
			firstHistogram(&fib_generator);
			break;
		case 4:	cout << d << endl;
			firstHistogram(&inver_generator);
			break;
		case 5: cout << f << endl;
			firstHistogram(&union_generator);
			break;
		case 6:	cout << j << endl;
			secondHistogram(&rule3_generator);
			break;
		case 7: cout << h << endl;
			secondHistogram(&polar_genrator);
			break;
		case 8: cout << k << endl;
			secondHistogram(&method_generator);
			break;
		case 9: cout << l << endl;
			thirdHistogram(&log_generator);
			break;
		case 10: cout << g << endl;
			thirdHistogram(&arens_generator);
			break;
		default: cout << "You choose an uncorrect value. ";
			break;
		}
	}
		system("pause");
}