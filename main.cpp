#include <iostream>
#include <stdio.h>
#include "src/cmp.h"
#include "src/list.h"
#include "src/btree.h"

using namespace std;

int main(int argc, char const *argv[]){

	list<int, cml<int>> *a = new list<int, cml<int>>();
	//btree<int, cml<int>> *a = new btree<int, cml<int>>();
	srand(time(NULL));
	int t = 80;
	for(int i=0; i<t; i++)	a->insert(rand()%t);
	a->print();
	return 0;
}
	
