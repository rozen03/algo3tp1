#include"kamehameha.h"

int main(int argc, char* argv[]){
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

int verticalDestroy(Android a){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a.posX << "," << a.posY << ")";
    string s = ss.str();
    for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
        if(it->posX == a.posX){
            if(it->state == "active"){
                it->state = s;
                it->kame = PARTIAL_KAMEHAMEHA;
                res ++;
            }
        }
    }
    return res;
}

int horizontalDestroy(Android a){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a.posX << "," << a.posY << ")";
    string s = ss.str();
    for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
        if(it->posY == a.posY){
            if(it->state == "active"){
                it->state = s;
                it->kame = PARTIAL_KAMEHAMEHA;
                res ++;
            }
        }
    }
    return res;
}

int horizontalRestore(Android a){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a.posX << "," << a.posY << ")";
    string s = ss.str();
    for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
        if(it->posY == a.posY){
            if(it->state == s){
                it->state = "active";
                res ++;
            }
        }
    }
    return res; //cantidad restaurada
}

int verticalRestore(Android a){
    int res = 0;
    stringstream ss;
    ss << "destroyed(" << a.posX << "," << a.posY << ")";
    string s = ss.str();
    for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
        if(it->posX == a.posX){
            if(it->state == s){
                it->state = "active";
                res ++;
            }
        }
    }
    return res; //cantidad restaurada
}

void backtrack(){
    if(REMAINING_ANDROIDS == 0){
        BEST_KAMEHAMEHA = PARTIAL_KAMEHAMEHA;    //mejor solucion encontrada hasta ahora
        SOLUTION = enemies;
    }
    else{
        for(vector<Android>::iterator it = enemies.begin(); it != enemies.end(); ++it){ //O(n)
            if(it->state == "active"){    //poda: solo seguimos si no esta destruido
                if(PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA){   //poda: a lo sumo es igual a la mejor solucion encontrada
                    PARTIAL_KAMEHAMEHA ++;
                    int res = horizontalDestroy(*it);  //destruimos todos los androides en la misma fila
                    REMAINING_ANDROIDS -= res;
                    backtrack();
                    res = horizontalRestore(*it);  //volmemos a como estaba antes
                    REMAINING_ANDROIDS += res;
                    PARTIAL_KAMEHAMEHA --;
                }
                if(PARTIAL_KAMEHAMEHA + 1 < BEST_KAMEHAMEHA){
                    PARTIAL_KAMEHAMEHA ++;
                    int res = verticalDestroy(*it);    //destruimos todos los androides en la misma columna
                    REMAINING_ANDROIDS -= res;
                    backtrack();
                    res = verticalRestore(*it);    //volvemos a como estaba antes
                    REMAINING_ANDROIDS += res;
                    PARTIAL_KAMEHAMEHA --;
                }
            }
        }
    }
}
