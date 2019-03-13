#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include "src/sws.cpp"

using namespace std;
//static int i,j;

void f(int *a, int &i, int &j, int &der, int &izq, int x){
	while((*(a+i)<x) and (j<=der))	i++;
}

void g(int *a, int &j, int &izq, int x){
	while((x<*(a+j)) and (j>izq))	j--;
}

void quick(int *a,int izq, int der){ 
    int i,j,x; 
    i = izq; 
    j = der; 
    x = *(a + (izq+der)/2); 
    thread th[2];
    do{ 
    	//th[0] = thread(&f, a, i, j, der, izq, x);
    	//th[1] = thread(&g, a, j, izq, x);
    	while(compare(*(a+i),x) and (j<=der))    i++;
        while(compare(x,*(a+j)) and (j>izq)) j--;
    	//th[0].join(); th[1].join();

        if(i<=j){ 
            swap1((a+i), (a+j));
            i++;  j--; 
        }
         
    }while(i<=j);
    

    if(izq<j){
    	th[0] = thread(quick, a, izq, j); 
    	//th[0].join();
    }
    if(i<der)  {
    	th[1] = thread(quick, a, i, der);
    	//th[1].join();
    }
    th[0].join(); th[1].join();
}


int main(int argc, char const *argv[]){
	int t = 100;
	int *a = new int[t];
	pull_al(a, t);
	quick(a, 0, t-1);
	print(a, t);
	return 0;
}