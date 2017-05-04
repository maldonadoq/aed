#include <iostream>
#include <stdio.h>
#include "src/dlista.h"
#include "src/cmp.h"

using namespace std;

int main(int argc, char const *argv[]){
	dlista<int, cm<int>> *a = new dlista<int, cm<int>>();
	int t=40, r;
	srand(time(NULL));
	for(int i=0; i<t; i++){
		r = rand()%t;
		cout << r << " ";
		a->insert(r);
	}
	cout << endl;
	a->print();
	a->printr();
	delete a;
	return 0;
}
