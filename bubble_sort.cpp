#include <iostream>
#include <stdio.h>
#include <thread>
#include "src/sws.cpp"

using namespace std;

void sort(int *a, int t, int w){
	for(int j=0; j<t-w; j++)
		if(*(a+j)<*(a+j+1))	swap1((a+j),(a+j+1));
}

void bubble_sort(int *a, int t){
	int th = thread::hardware_concurrency();
	thread h[th];
	int r = fn(t, th);
	for(int i=0; i<r; i++){
		for(int j=0; j<th; j++)	h[j] = thread(&sort, a, t, i);
		for(int j=0; j<th; j++)	h[j].join();
	}
}

int main(int argc, char const *argv[]){
	int t;
	cout << "tamaño:  "; cin >> t;
	//t = 100;
	int *a = new int[t];
	pull_al(a, t);
	
	double tim = time(a, t, bubble_sort);
    printf("time bubble_sort:       %.28f s\n", tim/1000);

	print(a, t);
	return 0;
}