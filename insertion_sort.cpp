#include <iostream>
#include <stdio.h>
#include <thread>
#include "srs/sws.cpp"

using namespace std;

static int w = 0;

void sort(int *a, int t){
	int j = w;
	while(j>0 and (*(a+j)<*(a+j-1))){
		swap1((a+j), (a+j-1));
		j--;
	}
	w++;
}

void insertion_sort(int *a, int t){
	int th = thread::hardware_concurrency();
	thread h[th];
	int r = fn(t, th);
	for(int i=0; i<r; i++){
		for(int j=0; j<th; j++)	h[j] = thread(&sort, a, t);
		for(int j=0; j<th; j++)	h[j].join();
	}
}

int main(int argc, char const *argv[]){
	int t;
	t = 100000;
	//cout << "tamaño:  "; cin >> t;
	
	int *a = new int[t];
	pull_al(a,t);
	
	double tim = time(a,t,insertion_sort);
    printf("time insertion_sort:       %.28f s\n", tim/1000);

	//print(a, t);
	return 0;
}