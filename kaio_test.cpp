#include <ctime>
#include <iostream>      /* printf */
#include <math.h>       /* log */
#include <stdlib.h>     /* atoi */
using namespace std;

void kaio(long n) {
	int rango = (int)(log(n) / log(2)) + 2;
	int i = 1;
	int x;
	if (n == (int)pow(2, rango - 2))
		rango -= 1;
	for (i = 1; i < rango; i++) {

		for (x = 0; x < n; x++) {
			if ((x % (int)pow(2, i)) < pow(2, i - 1)) {
				//cout << "1";
				i = i;
			} else {
				//cout << "2";
				i = i;
			}
			//if (x < n - 1) cout << " ";
		}
	}

}
int main(int argc, char const *argv[])
{
	long cant;
	cant = 10000000;
	for (long i = 1; i < cant; i++ ) {
		//cout<<i<<" ";
		clock_t begin = clock();
		kaio(i);
		clock_t end = clock();
		double elapsed_secs = double(end - begin) ;// CLOCKS_PER_SEC;
		// cout << "time[" << i << "]=" << elapsed_secs << "\n";
		cout << i << "    " << elapsed_secs << "\n";
	}
}

