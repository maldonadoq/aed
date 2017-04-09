#include <iostream>
#include <stdio.h>
#include <thread>
#include "src/sws.cpp"

using namespace std;

//static int w = 0;

void merge(int *a, int izq, int der, bool (*compare)(int, int)){
    if(izq == der)  
        return; 

    int t = der-izq+1; 
    int piv = (izq+der) / 2; 

    thread aj(merge, a, izq, piv, compare);
    thread ak(merge, a, piv+1, der, compare);
    aj.join(); ak.join();
    //merge(a, izq, piv, compare); 
    //merge(a, piv+1, der, compare);

    int *b = new int[t]; 
    for(int i=0; i<t; i++)  
        *(b+i) = *(a+izq+i); 	
    int j = 0;  
    int k = piv-izq+1; 

    for(int i = 0; i < t; i++) { 
        if(k <= der-izq)  
            if(j <= piv-izq)  
                if(compare(*(b+k),*(b+j)))	*(a+i+izq) = *(b+k++);
                else	*(a+i+izq) = *(b+j++); 
            else  
                *(a+i+izq) = *(b+k++); 
        else  
            *(a+i+izq) = *(b+j++); 
    } 
}

int main(int argc, char const *argv[]){
	int t = 10000;
	int *a = new int[t];
	pull_al(a, t);

	merge(a, 0,t-1,compare);
	//print(a, t);

	return 0;
}

/*

*/