#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "src/sws.h"
#include "src/cmp.h"
#include "src/lista.h"
#include "src/dlista.h"
#include "src/clista.h"

using namespace std;

int main(int argc, char const *argv[]){
	lista<int, cmg<int>> *a = new lista<int, cmg<int>>();
	int t=10;
	srand(time(NULL));
	for(int i=0; i<t; i++)	a->insert(rand()%t);
	a->print();
	a->bubble_sort();
	a->print();
	return 0;
}
