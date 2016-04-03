#include"kamehameha.h"

int main(int argc, char* argv[]){
    if(argc > 1){
        string s(argv[1]);
        if(s == "--test"){
            if(argc != 6){
		cout << "Modo de uso: ./kamehameha --test \"repeticiones\" \"cantidad\" \"n inicial\" \"incremento\" " << endl;
		return 0;
	        }
            repeticiones = atoi(argv[2]);
            cantidad = atoi(argv[3]);
            n_inicial = atoi(argv[4]);
	        incremento = atoi(argv[5]);
            runTest();
        }
        return 0;
    }

    // Chequeo si se llamo correctamente al programa
	if(isatty(STDIN_FILENO)){
		cout << "Modo de uso: echo \"entrada\" | ./kamehameha" << endl;
		return 0;
	}
    int n;
    cin >> n;
    REMAINING_ANDROIDS = n;
    for(int i=0; i < n; i++){
        int x,y;
        cin >> x;
        cin >> y;
        enemies.push_back(Android(x,y));
    }     
    backtrack();    
    cout << BEST_KAMEHAMEHA << '\n';
    vector<string> output(BEST_KAMEHAMEHA);
    vector<int> defeated(BEST_KAMEHAMEHA);
    for(vector<Android>::iterator it = SOLUTION.begin(); it != SOLUTION.end(); ++it){
        int i = it->kame -1;
        output[i].append(it->X()+' ');
        output[i].append(it->Y()+' ');
        defeated[i] ++; 
    }
    for(uint i=0; i < output.size(); i++){
        cout << defeated[i] << ' ' << output[i] << '\n';
    }
    return 0;
}

int destroy(Android* a, Android* b){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a->posX << "," << a->posY << ";"<< b->posX << "," << b->posY << ")";
    string s = ss.str();
    a->state = s;
    a->kame = PARTIAL_KAMEHAMEHA;
    res ++;
    b->state = s;
    b->kame = PARTIAL_KAMEHAMEHA;
    res ++;
    double angle = getAngle(*a,*b);
    for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
        if(it->state == "active"){
            if(angle == getAngle(*a,*it)){
                it->state = s;
                it->kame = PARTIAL_KAMEHAMEHA;
                res ++;
            }
        }
    }
    return res;
}

int destroy(Android* a){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a->posX << "," << a->posY << ")";
    string s = ss.str();
    a->state = s;
    a->kame = PARTIAL_KAMEHAMEHA;
    res ++;
    return res;
}

int restore(Android* a, Android* b){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a->posX << "," << a->posY << ";"<< b->posX << "," << b->posY << ")";
    string s = ss.str();
    a->state = "active";
    res ++;
    b->state = "active";
    res ++;
    double angle = getAngle(*a,*b);
    for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
        if(it->state == s){
            if(angle == getAngle(*a,*it)){
                it->state = "active";
                res ++;
            }
        }
    }
    return res; //cantidad restaurada
}

int restore(Android* a){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a->posX << "," << a->posY << ")";
    string s = ss.str();
    a->state = "active";
    res ++;
    return res; //cantidad restaurada
}

double getAngle(Android a, Android b){
    int y = a.posY - b.posY;
    int x = a.posX - b.posX;
    if(x == 0){
        return 9999;
    }
    else{
        return y/double(x);
    }
}

void backtrack(){
    if(REMAINING_ANDROIDS == 0){
        BEST_KAMEHAMEHA = PARTIAL_KAMEHAMEHA;    //mejor solucion encontrada hasta ahora
        SOLUTION.clear();
        SOLUTION = enemies;
    }
    else if(REMAINING_ANDROIDS == 1){
        if(PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA){   //poda: a lo sumo es igual a la mejor solucion encontrada
            for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
                if(it->state == "active"){
                    PARTIAL_KAMEHAMEHA ++;
                    int res = destroy(&(*it));
                    REMAINING_ANDROIDS -= res;
                    backtrack();
                    res = restore(&(*it));  //volmemos a como estaba antes
                    REMAINING_ANDROIDS += res;
                    PARTIAL_KAMEHAMEHA --;
                }    
            }
        }
    }
    else{
        for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
            if(it->state == "active"){    //poda: solo seguimos si no esta destruido
                for(vector<Android>::iterator itt = enemies.begin(); itt != enemies.end(); ++itt){ //O(n)
                    if(itt->state == "active"){    //poda: solo seguimos si no esta destruido
                        if(it != itt){ //poda: no tiene sentido iterar sobre si mismo
                            if(PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA){   //poda: a lo sumo es igual a la mejor solucion encontrada
                                PARTIAL_KAMEHAMEHA ++;
                                int res = destroy(&(*it),&(*itt));  //destruimos todos los androides en la recta entre it e itt
                                REMAINING_ANDROIDS -= res;
                                backtrack();
                                res = restore(&(*it),&(*itt));  //volmemos a como estaba antes
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

void runTest(){
    stringstream ss;
    generar(ss,repeticiones,cantidad,n_inicial,incremento);
    microseconds duration(0);
    int instancia = 0;
    char letra = ss.peek();
	while(letra != '#'){
        // Entrada
		int n;
        ss >> n;
        REMAINING_ANDROIDS = n;
        enemies.clear();
        for(int i=0; i < n; i++){
            int x,y;
            ss >> x;
            ss >> y;
            enemies.push_back(Android(x,y));
        }
        instancia ++;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();     
        backtrack();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration += duration_cast<microseconds>( t2 - t1 );
        if(instancia == repeticiones){
            cout << n << ' ' << uint64_t(duration.count() / instancia) << '\n';
            instancia = 0;
            duration = microseconds(0);
        }
        letra = ss.get(); // come el '\n'
		letra = ss.peek();
    }
}
