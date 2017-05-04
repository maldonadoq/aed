#ifndef _SORTTHREAD_H_
#define _SORTTHREAD_H_

#include <thread>
#include <mutex>
#include "sws.h"
#include "sort.h"

static int th = 4;
//static mutex *m = new mutex[th];
//8192

void bu_sort(int *a, int t, int *w, int y, mutex *m){
	lock_guard<mutex> locker(m[y]);
	for(int j=0; j<t-(*w); j++)
		if(*(a+j)>*(a+j+1))	swap1((a+j),(a+j+1));
	(*w)+=1;
}

void bubble_thread(int *a, int t){
	thread h[th];
    mutex *m = new mutex[th];
	int tm 	= 0;
	int *p = &tm;
	for(int i=0; i<t; i+=th){
		for(int j=0; j<th; j++)	h[j] = thread(&bu_sort,a,t,p,j,m);
		for(int j=0; j<th; j++)	h[j].join();
	}
    delete m;

	bool aux = true;
	for(int i=1; aux and i<=(t%th);i++){
	    aux = false;
	    for(int j=t-i;j>=0;j--){
	        if((*(a+j)>*(a+j+1))){
	            swap1((a+j),(a+j+1));
	            aux = true;
	        }
	    }
	}
}

void in_sort(int *a, int t, int *p, int y, mutex *m){
	lock_guard<mutex> locker(m[y]);
	int j = *p;
	while(j>0 and (*(a+j)<*(a+j-1))){
		swap1((a+j),(a+j-1));
		j--;
	}
	(*p)+=1;
}

void insertion_thread(int *a, int t){
	thread h[th];
    mutex *m = new mutex[th];
	int tm=(t/th), i=1;
	int *pt = &i;
	for(int k=0; k<tm; k++){
		for(int j=0; j<th; j++)	h[j] = thread(&in_sort,a, t,pt,j,m);
		for(int j=0; j<th; j++)	h[j].join();
	}
    delete m;
	int j, r=(tm*th);
    for(int i=r+1;i<t;i++){
        j = i;
        while(j>0 and (*(a+j)<*(a+j-1))){
            swap1((a+j),(a+j-1));
            j--;
       }
    }
}

void me_sort(int *a, int izq, int der, int *n_th){
    if(izq == der)  
        return; 

    int t = der-izq+1; 
    int piv = (izq+der) / 2; 

    (*n_th)+=2;
    if(*n_th<th){
	    thread aj(me_sort, a, izq, piv, n_th);
	    thread ak(me_sort, a, piv+1, der, n_th);
	    aj.join(); ak.join();
	}
	else{
		thread aj(merge, a, izq, piv);
	    thread ak(merge, a, piv+1, der);
	    aj.join(); ak.join();	
	}

    int *b = new int[t]; 
    for(int i=0; i<t; i++)  
        *(b+i) = *(a+izq+i); 	
    int j = 0;  
    int k = piv-izq+1; 

    for(int i = 0; i < t; i++) { 
        if(k <= der-izq)  
            if(j <= piv-izq)  
                if((*(b+k)<*(b+j)))	*(a+i+izq) = *(b+k++);
                else	*(a+i+izq) = *(b+j++); 
            else  
                *(a+i+izq) = *(b+k++); 
        else  
            *(a+i+izq) = *(b+j++); 
    }
    delete b;
}
void merge_thread(int *a, int t){
	int tm = 0;
	int *p = &tm;
	me_sort(a,0,t-1,p);	
}

void qu_sort(int *a,int izq, int der, int *p){ 
    int i,j,x; 
    i = izq; 
    j = der; 
    x = *(a + (izq+der)/2); 
    thread h[2];
    do{ 
    	while((*(a+i)<x) and (j<=der))    i++;
        while((x<*(a+j)) and (j>izq)) j--;
        if(i<=j){ 
            swap1((a+i), (a+j));
            i++;  j--; 
        }
         
    }while(i<=j);
    
    (*p)+=2;
    if(*p<th){
        if(izq<j)   h[0] = thread(qu_sort, a, izq, j,p); 
        if(i<der)   h[1] = thread(qu_sort, a, i, der,p);
        if(izq<j)   h[0].join(); 
        if(i<der)   h[1].join();
    }
    else{
        if(izq<j)   quick(a, izq, j); 
        if(i<der)   quick(a, i, der);
    }
}
void quick_thread(int *a, int t){
    int tm = 0;
    int *p = &tm;
    qu_sort(a,0,t-1,p);
}

#endif