#include <ctime>
#include <iostream>      /* printf */
#include <math.h>       /* log */
#include <stdlib.h>     /* atoi */
#include <algorithm>
#include <stdint.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

struct Android {
	int posX;
	int posY;
	string state;
	int kame;
	Android(int x, int y) {
		posX = x;
		posY = y;
		state = "active";   //activo o destruido con pos de quien lo destruyo
		kame = 0;   //numero de kamehameha que lo destruyo
	}
	string X() {
		stringstream ss;
		ss << posX;
		return ss.str();
	}
	string Y() {
		stringstream ss;
		ss << posY;
		return ss.str();
	}
	bool operator=(const Android& a) const {	//operator overload para "="
		if (posX == a.posX && posY == a.posY) {
			return true;
		}
		return false;
	}
};

// variable globales
int BEST_KAMEHAMEHA = 9999;
int PARTIAL_KAMEHAMEHA = 0;
int REMAINING_ANDROIDS;
vector<Android> enemies;
vector<Android> SOLUTION;
int repeticiones = 0;
int cantidad = 0;
int n_inicial = 0;
int incremento = 0;



class Distribucion {
public:
	vector<int> x;
	vector<int> y;

	Distribucion(int casos) {
		srand(clock());
		for (uint i = 0; i < casos; i++) {
			x.push_back(rand() % 10 * casos);
			y.push_back(rand() % 10 * casos);
		}
		sort(x.begin(), x.end(), greater<int>());
		sort(y.begin(), y.end(), less<int>());
	};

};

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
uint64_t rdtsc() {
	unsigned int lo, hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}

void medir_kaio() {
	long cant;
	cant = 10000;
	fstream result("medicion_kaio.txt", ios::out);

	uint repetir = 31415;
	uint64_t begin;
	uint64_t end ;
	uint64_t elapsed_secs, elapsed_final;
	elapsed_final = 0;
	elapsed_secs = 0;
	for (long i = 0; i < cant; i++ ) {
		for (int j = 0; j < repetir ; j++) {
			begin = rdtsc();
			kaio(i);
			end = rdtsc();
			elapsed_secs += double(end - begin);
		}
		// cout << "time[" << i << "]=" << elapsed_secs << "\n";
		elapsed_final = elapsed_secs / repetir;
		cout << i << "    " << elapsed_final << "    " << elapsed_secs << "\n";
		result << i << "    " << elapsed_final << "\n";
	}
	result.close();

}

#define mata(i, j) \
				((enemigos[j][0] <= enemigos[i][0]+ t) && ((enemigos[j][1] ) <= enemigos[i][1]+t))

int genki(uint t, uint n, Distribucion distribucion ) {
	//cin >> n >> t;
	int enemigos[n][2];
	for (uint i = 0; i < n; i++) {
		enemigos[i][0] = distribucion.x[i];
		enemigos[i][1] = distribucion.y[i];
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


int medir_genki(int casos, int t, char* output, vector<Distribucion>  distribucion) {
	//uint t, casos;
	fstream result(output, ios::out);
	int repetir = 31415;

	for (uint n = 0; n < casos; n++) {
		uint64_t elapsed_secs = 0;
		uint64_t elapsed_final = 0;
		result << n << "	";
		cout << n << "	";
		for (uint repeater = 0; repeater < repetir; repeater++) {	//t = 2*n;
			srand(time(NULL));
			uint64_t begin = rdtsc();
			genki(t, n, distribucion[n]);

			uint64_t end = rdtsc();
			elapsed_secs += end - begin;
		}
		elapsed_final = elapsed_secs / repetir;
		cout << elapsed_final << "  " << elapsed_secs << "\n";
		result << elapsed_final << "\n";
	}
	result.close();
}


int medir_genki_T_variable(int casos, char* output, Distribucion  distribucion) {
	//uint t, casos;
	fstream result(output, ios::out);
	int repetir = 31415;

	for (uint n = 0; n < 10 * casos; n++) {
		uint64_t elapsed_secs = 0;
		uint64_t elapsed_final = 0;
		result << n << "	";
		cout << n << "	";
		for (uint repeater = 0; repeater < repetir; repeater++) {	//t = 2*n;
			srand(time(NULL));
			uint64_t begin = rdtsc();
			genki(n, casos, distribucion);
			uint64_t end = rdtsc();
			elapsed_secs += end - begin;
		}
		elapsed_final = elapsed_secs / repetir;
		cout << elapsed_final << "  " << elapsed_secs << "\n";
		result << elapsed_final << "\n";
	}
	result.close();
}



double getAngle(Android a, Android b) {
	int y = a.posY - b.posY;
	int x = a.posX - b.posX;
	if (x == 0) {
		return 9999;
	}
	else {
		return y / double(x);
	}
}

int destroy(Android* a, Android* b) {
	int res = 0;
	stringstream ss;
	ss << "destroyed(" << a->posX << "," << a->posY << ";" << b->posX << "," << b->posY << ")";
	string s = ss.str();
	a->state = s;
	a->kame = PARTIAL_KAMEHAMEHA;
	res ++;
	b->state = s;
	b->kame = PARTIAL_KAMEHAMEHA;
	res ++;
	double angle = getAngle(*a, *b);
	for (vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it) { //O(n)
		if (it->state == "active") {
			if (angle == getAngle(*a, *it)) {
				it->state = s;
				it->kame = PARTIAL_KAMEHAMEHA;
				res ++;
			}
		}
	}
	return res;
}

int destroy(Android* a) {
	int res = 0;
	stringstream ss;
	ss << "destroyed(" << a->posX << "," << a->posY << ")";
	string s = ss.str();
	a->state = s;
	a->kame = PARTIAL_KAMEHAMEHA;
	res ++;
	return res;
}

int restore(Android* a, Android* b) {
	int res = 0;
	stringstream ss;
	ss << "destroyed(" << a->posX << "," << a->posY << ";" << b->posX << "," << b->posY << ")";
	string s = ss.str();
	a->state = "active";
	res ++;
	b->state = "active";
	res ++;
	double angle = getAngle(*a, *b);
	for (vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it) { //O(n)
		if (it->state == s) {
			if (angle == getAngle(*a, *it)) {
				it->state = "active";
				res ++;
			}
		}
	}
	return res; //cantidad restaurada
}

int restore(Android* a) {
	int res = 0;
	stringstream ss;
	ss << "destroyed(" << a->posX << "," << a->posY << ")";
	string s = ss.str();
	a->state = "active";
	res ++;
	return res; //cantidad restaurada
}


void backtrack_conPoda() {
	bool conPoda = true;
	if (REMAINING_ANDROIDS == 0) {
		BEST_KAMEHAMEHA = PARTIAL_KAMEHAMEHA;    //mejor solucion encontrada hasta ahora
		SOLUTION.clear();
		SOLUTION = enemies;
	}
	else if (REMAINING_ANDROIDS == 1) {
		if ((PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA) && conPoda ) { //poda: a lo sumo es igual a la mejor solucion encontrada
			for (vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it) { //O(n)
				if (it->state == "active") {
					PARTIAL_KAMEHAMEHA ++;
					int res = destroy(&(*it));
					REMAINING_ANDROIDS -= res;
					backtrack_conPoda();
					res = restore(&(*it));  //volmemos a como estaba antes
					REMAINING_ANDROIDS += res;
					PARTIAL_KAMEHAMEHA --;
				}
			}
		}
	}
	else {
		for (vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it) { //O(n)
			if ((it->state == "active") && conPoda) {  //poda: solo seguimos si no esta destruido
				for (vector<Android>::iterator itt = enemies.begin(); itt != enemies.end(); ++itt) { //O(n)
					if ((itt->state == "active") && conPoda) {  //poda: solo seguimos si no esta destruido
						if (it != itt) { //poda: no tiene sentido iterar sobre si mismo
							if ((PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA) && conPoda) { //poda: a lo sumo es igual a la mejor solucion encontrada
								PARTIAL_KAMEHAMEHA ++;
								int res = destroy(&(*it), &(*itt)); //destruimos todos los androides en la recta entre it e itt
								REMAINING_ANDROIDS -= res;
								backtrack_conPoda();
								res = restore(&(*it), &(*itt)); //volmemos a como estaba antes
								REMAINING_ANDROIDS += res;
								PARTIAL_KAMEHAMEHA --;
							}
						}
					}
				}
			}
		}
	}
}

void backtrack_sinPoda() {
	if (REMAINING_ANDROIDS == 0) {
		BEST_KAMEHAMEHA = PARTIAL_KAMEHAMEHA;    //mejor solucion encontrada hasta ahora
		SOLUTION.clear();
		SOLUTION = enemies;
	}
	else if (REMAINING_ANDROIDS == 1) {
			for (vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it) { //O(n)
				if (it->state == "active") {
					PARTIAL_KAMEHAMEHA ++;
					int res = destroy(&(*it));
					REMAINING_ANDROIDS -= res;
					backtrack_sinPoda();
					res = restore(&(*it));  //volmemos a como estaba antes
					REMAINING_ANDROIDS += res;
					PARTIAL_KAMEHAMEHA --;
				}
			}
		
	}
	else {
		for (vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it) { //O(n)
				for (vector<Android>::iterator itt = enemies.begin(); itt != enemies.end(); ++itt) { //O(n)
						if (it != itt) { //poda: no tiene sentido iterar sobre si mismo
								PARTIAL_KAMEHAMEHA ++;
								int res = destroy(&(*it), &(*itt)); //destruimos todos los androides en la recta entre it e itt
								REMAINING_ANDROIDS -= res;
								backtrack_sinPoda();
								res = restore(&(*it), &(*itt)); //volmemos a como estaba antes
								REMAINING_ANDROIDS += res;
								PARTIAL_KAMEHAMEHA --;
							
						}
					
				}
			
		}
	}
}






int kamehameha(int n, int x[], int y[], bool conPoda) {

	REMAINING_ANDROIDS = n;
	BEST_KAMEHAMEHA = 9999;
	PARTIAL_KAMEHAMEHA = 0;
	enemies.clear();
	SOLUTION.clear();
	for (int i = 0; i < n; i++) {
		enemies.push_back(Android(x[i], y[i]));
	}
	if (conPoda) {
		backtrack_conPoda();
	} else {
		backtrack_sinPoda();
	}
	// cout << BEST_KAMEHAMEHA << '\n';
	// vector<string> output(BEST_KAMEHAMEHA);
	// vector<int> defeated(BEST_KAMEHAMEHA);
	// int index = 1;
	// for (vector<Android>::iterator it = SOLUTION.begin(); it != SOLUTION.end(); ++it) {
	// 	int i = it->kame - 1;
	// 	output[i].append(to_string(index) + ' ');
	// 	defeated[i] ++;
	// 	index++;
	// }
	// for (uint i = 0; i < output.size(); i++) {
	// 	cout << defeated[i] << ' ' << output[i] << '\n';
	// }
	return 0;
}



void medir_kame(int mode, bool conPoda, char* output) {
	int valores = 200;
	int inicial = 1;
	int incremento = 1;
	int valores_x[valores][valores];
	int valores_y[valores][valores];
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);
	uniform_int_distribution<int> puntos(1, 999);
	for (int i = 0; i < valores; i++) {
		uniform_int_distribution<int> coordenadas(1, puntos(generator));
		int n = inicial + i * incremento;
		if (mode == 0) {
			int x = coordenadas(generator);
			int y = coordenadas(generator);
			for (int j = 0; j < n; j++) {
				valores_x[i][j] = x;
				valores_y[i][j] = y;
				x++;
			}
		}
		else if (mode == 1) {
			for (int j = 0; j < n; j++) {
				int x = coordenadas(generator);
				int y = coordenadas(generator);
				valores_x[i][j] = x;
				valores_y[i][j] = y;
			}
		}
		else {
			int x = coordenadas(generator);
			for (int j = 0; j < n; j++) {
				valores_x[i][j] = x;
				valores_y[i][j] = x * x;
				x++;
			}
		}

	}

	long cant;
	cant = valores;
	fstream result(output, ios::out);

	uint repetir = 100;
	uint64_t begin;
	uint64_t end ;
	uint64_t elapsed_secs, elapsed_final;
	elapsed_final = 0;
	elapsed_secs = 0;
	for (long i = 0; i < cant; i++ ) {
		for (int j = 0; j < repetir ; j++) {
			begin = rdtsc();
			kamehameha(i, valores_x[i], valores_y[i], conPoda);
			end = rdtsc();
			elapsed_secs += double(end - begin);
		}
		// cout << "time[" << i << "]=" << elapsed_secs << "\n";
		elapsed_final = elapsed_secs / repetir;
		cout << i << "    " << elapsed_final << "    " << elapsed_secs << "\n";
		result << i << "    " << elapsed_final << "\n";
	}
	result.close();

}




int main() {
	// medir_kaio();


	// int genki_casos = 3000;
	// vector<Distribucion> distribuciones;
	// for (int i = 0; i < genki_casos; i++) {
	// 	distribuciones.push_back(Distribucion(i));
	// }
	// medir_genki(genki_casos, 1, "resultado_genki_T1.txt", distribuciones);
	// medir_genki(genki_casos, 10, "resultado_genki_T10.txt", distribuciones);
	// medir_genki(genki_casos, 50, "resultado_genki_T50.txt", distribuciones);
	// medir_genki(genki_casos, 100, "resultado_genki_T100.txt", distribuciones);
	// Distribucion distribucionBase = Distribucion(genki_casos);
	// medir_genki_T_variable(genki_casos, "resultado_genki_T_variable.txt", distribucionBase);



	//sin poda
	medir_kame(0, false, "medicion_mejor_sinPoda.txt");
	medir_kame(1, false, "medicion_promedio_sinPoda.txt");
	medir_kame(2, false, "medicion_peor_sinPoda.txt");
	//con poda
	medir_kame(0, true, "medicion_mejor_conPoda.txt");
	medir_kame(1, true, "medicion_promedio_conPoda.txt");
	medir_kame(2, true, "medicion_peor_conPoda.txt");
}