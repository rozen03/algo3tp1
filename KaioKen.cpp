#include <iostream>      
#include <math.h>       
#define GRUPO_1 1
#define GRUPO_2 2
using namespace std;

int main(int argc, char* argv[]) {
	int n; /* Parametro de entrada del problema */
	int i, x, rango;

	cin >> n;
	
	/* Determina la mitad del vector, tiene en cuenta si es par o impar (redondea para arriba) */
	rango = (int)(log(n) / log(2)) + 2;
	if (n == (int)pow(2, rango - 2)) rango -= 1;

	/* Imprime por stdout la cantidad de soluciones *///
	cout << rango - 1 << endl;

	i = 1;
	for (i = 1; i < rango; i++) {
		x = 0;
		for (x = 0; x < n; x++) {
			if ((x % (int)pow(2, i)) < pow(2, i - 1)) {
				cout << GRUPO_1;
			} 
			else {
				cout << GRUPO_2;
			}
			if (x < n - 1) cout << " ";
		}
		cout << endl;
	}

} 
