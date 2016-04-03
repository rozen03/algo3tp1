#include <iostream>      /* printf */
#include <math.h>       /* log */
#include <stdlib.h>     /* atoi */
using namespace std;

int main(int argc, char* argv[]) {
	//int n = atoi(argv[1]);
	int n;
	cin>>n;
	int rango = (int)(log(n) / log(2)) + 2;
	if (n == (int)pow(2, rango - 2))
		rango -= 1;
	cout << rango - 1 << "\n";
	int i = 1;
	for (i = 1; i < rango; i++) {
		int x = 0;
		for (x = 0; x < n; x++) {
			if ((x % (int)pow(2, i)) < pow(2, i - 1)) {
				cout << "1";
			} else {
				cout << "2";
			}
			if (x < n - 1) cout << " ";
		}
		cout << "\n";
	}

}