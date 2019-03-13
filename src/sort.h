#ifndef _SORT_H_
#define _SORT_H_

#include "sws.h"

void bubble_sort(int *a, int t){
    bool aux = true;
    for(int i=1; aux and i<t;i++){
        aux = false;
        for(int j=0;j<t-i;j++){
            if((*(a+j)>*(a+j+1))){
                swap1((a+j),(a+j+1));
                aux = true;
            }
        }
    }
}

void insertion_sort(int *a, int t){
    int j;
    for(int i=0;i<t;i++){
        j = i;
        while(j>=0 and (*(a+j+1)<*(a+j))){
            swap1((a+j+1),(a+j));
            j--;
        }
    }
}

void merge(int *a, int izq, int der){
    if(izq == der)  
        return; 

    int t = der-izq+1; 
    int piv = (izq+der) / 2; 

    merge(a, izq, piv); 
    merge(a, piv+1, der);

    int *b = new int[t]; 
    for(int i=0; i<t; i++)  
        *(b+i) = *(a+izq+i); 
    int j = 0;  
    int k = piv-izq+1; 

    for(int i = 0; i < t; i++) { 
        if(k <= der-izq)  
            if(j <= piv-izq)  
                if((*(b+k)<*(b+j))){
                    *(a+i+izq) = *(b+k++); 
                }
                else  
                    *(a+i+izq) = *(b+j++); 
            else  
                *(a+i+izq) = *(b+k++); 
        else  
            *(a+i+izq) = *(b+j++); 
    }
    delete b;
}

void merge_sort(int *a, int t){ merge(a, 0, t-1);   }

void quick(int *a,int izq, int der){ 
    int i, j, x; 
    i = izq; 
    j = der; 
    x = *(a + (izq+der)/2); 
    do{ 
        while((*(a+i)<x) and (j<=der))    i++;
        while((x<*(a+j)) and (j>izq)) j--;
 
        if(i<=j){ 
            swap1((a+i), (a+j));
            i++;  j--; 
        }
         
    }while(i<=j);
    
    if(izq<j)  quick(a, izq, j); 
    if(i<der)  quick(a, i, der);
}
void quick_sort(int *a, int t){     quick(a, 0, t-1);  }


#endif