#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "src/cmp.h"
#include "src/avl.h"

using namespace std;

int main(int argc, char const *argv[]){
	avl<int, cmg<int> > *a = new avl<int, cmg<int> >();
	int t=13;
	srand(time(NULL));
	for(int i=1; i<=t; i++)	a->insert(i);
	//for(int i=t-1; i>0; i--)	a->remove(i);
	a->remove(13);
	a->remove(12);
	a->remove(11);
	a->remove(10);
	delete a;
	return 0;
}