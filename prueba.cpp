#include <iostream>
#include <stdio.h>
#include "src/sws.h"
#include "src/sort.h"
#include "src/sort_t.h"
#include <list>

FILE *A;

using namespace std;

int main(int argc, char const *argv[]){
	int nv=32, nt=8;
	int pr[nv] = {100,200,300,400,500,1000,2000,3000,4000,5000,10000,20000,30000,40000,50000,100000,200000,300000,400000,500000,1000000,2000000,3000000,4000000,5000000,10000000,20000000,30000000,40000000,50000000,100000000,200000000};
	int nth[nt] = {3,4,5,10,50,100,150,200};

	A = fopen("../datos/merge_sort.dat","w");

	for(int i=0; i<nv; i++){
		fprintf(A, "%d\t", pr[i]);
		int *b = new int[pr[i]];
		p(b,pr[i]);
		dat_t(A,b,pr[i],merge_sort);
		delete b;
		for(int j=0; j<nt; j++){
			th = nth[j];
			int *a = new int[pr[i]];
			p(a,pr[i]);
			dat_t(A,a,pr[i],merge_thread);
			delete a;
		}
		fprintf(A, "%s", "\n");
	}
	fclose(A);
	return 0;
}
//plot "name_sort.dat" using 1:2 w l,'' using 1:3  w l,'' using 1:4  w l,'' using 1:5  w l,'' using 1:6  w l,'' using 1:7  w l,'' using 1:8  w l,'' using 1:9  w l,'' using 1:10  w l
