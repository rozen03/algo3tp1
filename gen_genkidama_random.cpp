#include <cstdio>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]) {
	int n, t;
	srand(time(NULL));
	t = rand() % 50;
	srand(time(NULL) + t % 100);
	n = rand() % 100000;
	cout << n << endl << t << endl;
	int j = n;
	for (int i = 0; j < n; j++) {
		cout << j-- << endl;
		cout << i << endl;
	}
}

