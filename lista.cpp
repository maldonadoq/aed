#include <iostream>
#include <stdio.h>
#include "src/cmp.h"
#include "src/dlista.h"
#include "src/clista.h"

using namespace std;

int main(int argc, char const *argv[]){
	//dlista<int, cml<int>> *a = new dlista<int, cml<int>>();
	clista<int, cml<int>> *a = new clista<int, cml<int>>();
	int t=20, r;
	//cout << "tamaño: "; cin >> t;
	srand(time(NULL));
	for(int i=0; i<t; i++){
		r = rand()%t;
		cout << r << " ";
		a->insert(r);
	}
	cout << endl;
	a->print();
	delete a;
	return 0;
}
