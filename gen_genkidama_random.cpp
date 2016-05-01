//#include <cstdio>
#include <iostream>
//#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <stdint.h>
#include <fstream>
using namespace std;
#define mata(i, j) \
				((enemigos[j][0] <= enemigos[i][0]+ t) && ((enemigos[j][1] ) <= enemigos[i][1]+t))

int genki(uint t, uint n, int x[], int y[] ) {
	//cin >> n >> t;
	int enemigos[n][2];
	for (uint i = 0; i < n; i++) {
		enemigos[i][0] = x[i];
		enemigos[i][1] = y[i];
	}
	uint sols[n];
	uint j;
	uint index_sols = 0;
	uint hasta_j = 0;
	uint i;
	i = 0;
	while (i < n) {
		j = i;
		while ((j < n) && mata(j, i)) {
			j++;
		}
		j--;
		//tiro la genkidama
		sols[index_sols] = j + 1;
		index_sols++;
		//me fijo hasta donde llega
		hasta_j = j;
		while (hasta_j < n && mata(j, hasta_j)) {
			hasta_j++;
		}
		i = hasta_j;
	}
	//cout << index_sols << "\n";
	for (i = 0; i < index_sols; i++) {
		i = i;
	}
	//	cout << sols[i] << " ";
//}
}
uint64_t rdtsc() {
	unsigned int lo, hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}

int main() {
	uint t, casos;
	fstream result("result_genki_random6.txt", ios::out);
	casos = 2000;
	uint repetir = 31415;
	for (uint n = 0; n < casos; n++) {
		uint64_t elapsed_secs = 0;
		uint64_t elapsed_final = 0;
		result << n << "	";
		cout << n << "	";
		for (uint repeater = 0; repeater < repetir; repeater++) {	//t = 2*n;
			srand(time(NULL));

			t = rand() % 2*n;	//caso promedio
			//t = 0; 				//peor caso
			//t = n * 1000;			//mejor caso
			int x[n];
			int y[n];
			//srand(time(NULL) + t % 100);
			for (uint i = 0; i < n; i++) {
				x[i] = rand() % 10 * n;
				y[i] = rand() % 10 * n;
			}
			sort(x, x + n, greater<int>());
			sort(y, y + n, less<int>());
			//clock_t begin = clock();
			//cout<<y[n]<<endl;
			uint64_t begin = rdtsc();
			genki(t, n, x, y);

			//clock_t end = clock();
			uint64_t end = rdtsc();
			elapsed_secs += end - begin;
		}
		elapsed_final = elapsed_secs / repetir;
		cout << elapsed_final << "  " << elapsed_secs << "\n";
		result << elapsed_final << "\n";
	}
	result.close();
}

