#include <chrono>
#include <time.h>
#include <random>
#include <iostream>
#include <sstream>

#define BEST 0
#define AVERAGE 1
#define WORST 2

using namespace std;

void generar(stringstream& ss, int repeticiones,int valores, int inicial,int incremento, int mode);
