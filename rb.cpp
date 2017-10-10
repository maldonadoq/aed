#include <iostream>
#include <stdio.h>
#include "src/cmp.h"
#include "src/redblack.h"

using namespace std;

typedef rbtree<int,cmg<int> > RB;
int main(int argc, char const *argv[]){
	RB *t = new RB();
	int r = 5;
	for(int i=0; i<r; i++){	t->insert(i);	t->print();	}
	
	for(int i=0; i<r; i++){	t->remove(i);	t->print();	}
	delete t;
	return 0;
}