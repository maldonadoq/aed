#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/sort.cpp"

using namespace std;

template<typename T>
T v_ab(T a){
	if(a < 0)	return 0-a;
	return a;
}


int main(int argc, char const *argv[]){
	int t, aux;
	//cout << "numeros a ordenar:  "; cin >> t;
    t = 20;
    srand(time(NULL));
	
    int *A = new int[t];
	int *B = new int[t];
	int *C = new int[t];
	int *D = new int[t];

    for(int i=0; i<t; i++){
    	aux = rand()%100;
    	A[i] = aux;
    	B[i] = aux;
    	C[i] = aux;
    	D[i] = aux;
    }

    thread a(bubble_sort, A, t, compare);
    thread b(insertion_sort, B, t, compare);
    thread c(quick_sort, C, 0, t-1, compare);
    thread d(merge_sort, D, 0, t-1, compare);

    a.join(); 
    b.join(); 
    c.join(); 
    d.join();
    
    print(A, t);
    print(B, t); 
    print(C, t);
    print(D, t);

    delete []A; delete []B; 
    delete []C; delete []D;
	return 0;
}	
