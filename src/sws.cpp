#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

void swap1(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

bool compare(int a, int b){
    if(a>b)    return  true;
    else    return false;
    //return (v_ab<int>(a)<v_ab<int>(b))? true: false;
}

void print(int *a, int t){
    for(int i=0; i<t; i++)  cout << *(a+i) << " ";
    cout << endl;
}

double time(int *a, int t, void (*p)(int *, int)){
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    p(a, t);

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    return tiempo;
}

void pull_al(int *a, int t){
    srand(time(NULL));
    for(int i=0; i<t; i++){
        *(a+i) = rand()%t;
    }
}

int fn(int t, int th){
    int r = t/th;
    if(t%th != 0)   r++;
    return r;
}