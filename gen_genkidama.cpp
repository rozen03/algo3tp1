#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int n, t;

	cin >> n;
	cin >> t;

	cout << n << endl;
	cout << t << endl;
	
	int j = n;
	for (int i = 0; i < n; i++) {
		cout << j-- << endl;
		cout << i << endl;
	}
}
