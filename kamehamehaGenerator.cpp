#include "kamehamehaGenerator.h"

using namespace std;

void generar(stringstream& ss, int repeticiones,int valores, int inicial,int incremento, int mode){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_int_distribution<int> puntos(1,999);
    for(int i=0; i < valores;i++){
        for(int k = 0; k < repeticiones; k++){
            uniform_int_distribution<int> coordenadas(1,puntos(generator));
            int n = inicial +i*incremento;
            ss << n;
            if(mode == BEST){
                int x = coordenadas(generator);
                int y = coordenadas(generator);
                for(int j=0; j < n; j++){
                    ss << ' ' << x << ' ' << y;
                    x++;        
                }    
            }
            else if(mode == AVERAGE){
                for(int j=0; j < n;j++){
	        	    int x = coordenadas(generator);
	        	    int y = coordenadas(generator);
	        	    ss << ' ' << x << ' ' << y; 				
                }
            }
            else{
                int x = coordenadas(generator);
                for(int j=0; j < n; j++){
                    ss << ' ' << x << ' ' << x*x;
                    x++;            
                }    
            }
            ss<<'\n';
        }
    }
    ss << '#';
}
