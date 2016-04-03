#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include<unistd.h>

using namespace std;

struct Android{
    int posX;
    int posY;
    string state;
    int kame;
    Android(int x, int y){
        posX = x;
        posY = y;
        state = "active";   //activo o destruido con pos de quien lo destruyo
        kame = 0;   //numero de kamehameha que lo destruyo
    }
    string X(){
        stringstream ss;
        ss << posX;
        return ss.str();
    }
    string Y(){
        stringstream ss;
        ss << posY;
        return ss.str();
    }
};

// variable globales
int BEST_KAMEHAMEHA = 9999;
int PARTIAL_KAMEHAMEHA = 0;
int REMAINING_ANDROIDS;
vector<Android> enemies;
vector<Android> SOLUTION;


int verticalDestroy(Android a);
int verticalRestore(Android a);
int horizontalDestroy(Android a);
int horizontalRestore(Android a);
void backtrack();
