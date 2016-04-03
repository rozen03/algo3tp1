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
    bool operator=(const Android& a) const{	//operator overload para "="
		if (posX == a.posX && posY == a.posY){	
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


int destroy(Android* a, Android* b);
int destroy(Android* a);
int restore(Android* a, Android* b);
int restore(Android* a);
double getAngle(Android a, Android b);
void backtrack();
