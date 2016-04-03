#include <iostream>      /* printf */
#include <stdlib.h>     /* atoi */
using namespace std;

#define mata(i, j) \
				((enemigos[j][0] <= enemigos[i][0]+ t) & ((enemigos[j][1] ) <= enemigos[i][1]+t))


int main(int argc, char* argv[]) {
	int t;
	int n;
	cin >> n >> t;
	int enemigos[n][2];
	int sols[n];
	int j;
	int index_sols = 0;
	int hasta_j = 0;
	int i;
	int x,y;
	for (i = 0; i < n; i++) {
		cin >> enemigos[i][0];
		cin >> enemigos[i][1];
	}
	i = 0;
	while (i < n) {
		j = i;
		while ((j < n) and mata(j, i))
			j++;
		j--;
		//tiro la genkidama
		sols[index_sols] = j+1;
		index_sols++;
		//me fijo hasta donde llega
		hasta_j = i;
		while (hasta_j < n and mata(i, hasta_j))
			hasta_j++;
		i = hasta_j;

	}
	cout<<index_sols<<"\n";
	for(i=0; i<index_sols;i++){
		cout<<sols[i]<<" ";
	}
}