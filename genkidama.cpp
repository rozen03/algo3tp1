#include <iostream> 
#include <stdlib.h> 
#define X 0
#define Y 1
#define EJES 2
#define mata(i, j) ((enemigos[j][X] <= enemigos[i][X]+ t) && ((enemigos[j][Y] ) <= enemigos[i][Y]+t))
using namespace std;

int main(int argc, char* argv[]) {
	int n, t; /* Parametros de entrada del problema */
	int i, j, hasta_j = 0, cantSoluciones = 0;
	int **enemigos;
	int *soluciones;

	cin >> n >> t;

	/* Dimensiona los vectores de enemigos y soluciones */
	enemigos = new int *[n];
	for (int k = 0; k < n; k++) enemigos[k] = new int[EJES];
	soluciones = new int[n];

	/* Ubica los enemigos */
	for (i = 0; i < n; i++) {
		cin >> enemigos[i][X];
		cin >> enemigos[i][Y];
	}
	i = 0;
	while (i < n) {
		/* Se para en cada enemigo desde el principio y verifica cual es el enemigo mas lejano que lo tiene en su alcance 
		 * se puede pensar que empieza desde arriba a la izquierda y va bajando hasta que encuentra un enemigo que
		 * que no mata al enemigo sobre el cual empezamos a iterar (en este caso i) si se tirara ahi la Genkidama*/
		j = i;
		while ((j < n) && mata(j, i))	j++;
		j--;
		
		/* Una vez que lo encuentra se fija ahora cuantos mata despues de donde se tira la Genkidama
		 * se puede pensar que ahora busca los enemigos a la derecha de donde se tira la Genkidama 
		 * hasta que encuentre uno que no sea alcanzado por la Genkidama */
		soluciones[cantSoluciones] = j + 1; /* Aumenta en 1 la cantidad necesaria de tiros */
		cantSoluciones++;
		hasta_j = j;
		while (hasta_j < n && mata(j, hasta_j))	hasta_j++;
		i = hasta_j;
	}

	/* Imprime los resultados por stdout */
	cout << cantSoluciones << "\n";
	for (i = 0; i < cantSoluciones; i++) {
		cout << soluciones[i] << " ";
	}

	/* Libera la memoria de los vectores pedidos */
	delete []soluciones;
	for (int k = 0; k < n; k++) delete []enemigos[k];
	delete []enemigos;
} 
