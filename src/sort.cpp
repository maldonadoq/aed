#include <iostream>
#include <thread>
#include "sws.cpp"

using namespace std;

static int cont_1 = 0;
static int cont_2 = 0;

void bubble_sort(int *a, int t, bool (*compare)(int,int)){
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    int cont=0, aux=1;

    for(int i=1;aux!=0 and i<t;i++){
        aux = 0;
        for(int j=0;j<t-i;j++){
            cont++;
            if(compare(*(a+j+1),*(a+j))){
                swap1((a+j+1),(a+j));
                aux+=1;
            }
        }
    }

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time bubble_sort:       %.28f s    if: %i\n", tiempo/1000, cont);
}

void insertion_sort(int *a, int t, bool (*compare)(int, int)){
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    int cont=0, j;
    for(int i=1;i<t;i++){
        j = i;
        while(j>0 and compare(*(a+j),*(a+j-1))){
            swap1((a+j),(a+j-1));
            j--;
        }
    }

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time insertion_sort:    %.28f s    if: %i\n", tiempo/1000, cont);
}

void quick(int *a,int izq, int der , bool (*compare)(int, int)){ 
    int i, j, x; 
    i = izq; 
    j = der; 
    x = *(a + (izq+der)/2); 
    do{ 
        while(compare(*(a+i),x) and (j<=der))    i++;     cont_1++;
        while(compare(x,*(a+j)) and (j>izq)) j--;   cont_1++;
 
        if(i<=j){ 
            swap1((a+i), (a+j));
            i++;  j--; 
        }
         
    }while(i<=j);
    
    if(izq<j)  quick(a, izq, j, compare); 
    if(i<der)  quick(a, i, der, compare);
}

void quick_sort(int *a,int izq, int der , bool (*compare)(int, int)){ 
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    
    quick(a, izq, der, compare);

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time quick_sort:        %.28f s    if: %i\n", tiempo/1000, cont_1);
}

void merge(int *a, int izq, int der, bool (*compare)(int, int)){
    if(izq == der)  
        return; 

    int t = der-izq+1; 
    int piv = (izq+der) / 2; 

    merge(a, izq, piv, compare); 
    merge(a, piv+1, der, compare);

    int *b = new int[t]; 
    for(int i=0; i<t; i++)  
        *(b+i) = *(a+izq+i); 
    int j = 0;  
    int k = piv-izq+1; 

    for(int i = 0; i < t; i++) { 
        if(k <= der-izq)  
            if(j <= piv-izq)  
                if(compare(*(b+k),*(b+j))){
                    *(a+i+izq) = *(b+k++); 
                    cont_2++;  
                }
                else  
                    *(a+i+izq) = *(b+j++); 
            else  
                *(a+i+izq) = *(b+k++); 
        else  
            *(a+i+izq) = *(b+j++); 
    } 
}

void merge_sort(int *a, int izq, int der, bool (*compare)(int, int)){
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    
    merge(a,izq,der,compare);

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time merge_sort:        %.28f s    if: %i\n", tiempo/1000, cont_2);   
}

void heap_sort(){

}