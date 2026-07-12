#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "mySort.h"
using namespace std;

long long compareCount = 0;
long long assignCount = 0;
ofstream csv;

void csvLine(string s) { csv << s << endl; }

double UniformRand(double a, double b) {
    return a + rand() * (b - a) / RAND_MAX;
}

double GaussRand(double mean, double variance) {
    static double u, v;
    static int phase = 0;
    double z;
    if(phase == 0) {
        u = (rand() + 1.0) / (RAND_MAX + 1.0);
        v = (rand() + 1.0) / (RAND_MAX + 1.0);
        z = sqrt(-2.0 * log(u)) * sin(2.0 * M_PI * v);
    } else {
        z = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
    }
    phase = 1 - phase;
    return mean + z * sqrt(variance);
}

double gettime(int restart=0) {
    const double c = 1.0 / CLOCKS_PER_SEC;
    static clock_t t = clock();
    if(restart) t = clock();
    return c * (clock() - t);
}

void InitData(int *data, int n, int flag) {
    switch(flag) {
        case -1: for(int i=0; i<n; i++) data[i] = n-1-i; break;
        case 0:  for(int i=0; i<n; i++) data[i] = i; break;
        case 1:  for(int i=0; i<n; i++) data[i] = (int)UniformRand(54,90); break;
        case 2:  for(int i=0; i<n; i++) data[i] = (int)GaussRand(72,36); break;
    }
}

void CopyArray(int *dest, int *src, int n) {
    for(int i=0; i<n; i++) dest[i] = src[i];
}

void TestOne(const char *name, const char *shortName, void (*sortFunc)(int*, int),
             const char *dataType[], int sizes[], int numSizes) {
    cout << endl << "====== " << name << " ======" << endl;
    for(int flag = -1; flag <= 2; flag++) {
        cout << endl << dataType[flag+1] << ":" << endl;
        cout << "size	time(s)	compares	assigns" << endl;
        for(int s = 0; s < numSizes; s++) {
            int n = sizes[s];
            int *orig = new int[n];
            int *data = new int[n];
            InitData(orig, n, flag);
            CopyArray(data, orig, n);
            compareCount = 0; assignCount = 0;
            gettime(1);
            sortFunc(data, n);
            double tu = gettime();
            cout << n << "	" << tu << "		" << compareCount << "		" << assignCount << endl;
            char buf[200];
            sprintf(buf, "%s,%s,%d,%.6f,%lld,%lld", shortName, dataType[flag+1], n, tu, compareCount, assignCount);
            csvLine(buf);
            delete[] orig; delete[] data;
        }
    }
}

int main() {
    srand(time(NULL));
    const char *dt[] = {"reverse", "ordered", "uniform", "normal"};
    int sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536};
    int ns = 7;

    csv.open("ShellSort_Results.csv");
    csvLine("algorithm,data_type,size,time_sec,compare_count,assign_count");

    TestOne("Shell original (gap/2)", "Shell_original", ShellSort, dt, sizes, ns);
    TestOne("Hibbard", "Hibbard", ShellSort_Hibbard, dt, sizes, ns);
    TestOne("Sedgewick", "Sedgewick", ShellSort_Sedgewick, dt, sizes, ns);

    // comparison (n=65536 normal)
    cout << endl << "====== Comparison (n=65536, normal) ======" << endl;
    cout << "version	time(s)	compares	assigns" << endl;
    int n = 65536;
    int *orig = new int[n];
    int *data = new int[n];
    InitData(orig, n, 2);

    CopyArray(data, orig, n);
    compareCount = 0; assignCount = 0; gettime(1);
    ShellSort(data, n);
    cout << "original	" << gettime() << "		" << compareCount << "		" << assignCount << endl;

    CopyArray(data, orig, n);
    compareCount = 0; assignCount = 0; gettime(1);
    ShellSort_Hibbard(data, n);
    cout << "Hibbard	" << gettime() << "		" << compareCount << "		" << assignCount << endl;

    CopyArray(data, orig, n);
    compareCount = 0; assignCount = 0; gettime(1);
    ShellSort_Sedgewick(data, n);
    cout << "Sedgewick	" << gettime() << "		" << compareCount << "		" << assignCount << endl;

    delete[] orig; delete[] data;
    csv.close();
    cout << endl << "CSV saved: ShellSort_Results.csv" << endl;
    cout << "Press Enter...";
    cin.get();
    return 0;
}