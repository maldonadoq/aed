#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <sys/time.h>
#include <utility>

using namespace std;

typedef unsigned long long ll;

void f1(int t, int id, ll *s){
	*(s+id) = 0;
	for(int i=0; i<t; i++)
		for(int j=0; j<t; j++)
			for(int k=0; k<t; k++)
				(*(s+id))+=1;
}

inline void f2_1(int x, ll *s){
	*s = 0;
	for(int j=0; j<x; j++)
		for(int k=0; k<x; k++)
			(*s)+=1;
}

void f2(int nu, int id, ll *r){
	int t = thread::hardware_concurrency();
	ll *comp = new ll[t];
	thread th[t];
	int div = nu/t, m = nu%t;
	*(r+id) = 0;

	for(int i=0; i<div; i++){
		for(int j=0; j<t; j++)	th[j] = thread(&f2_1,nu,(comp+j));
		for(int j=0; j<t; j++)	th[j].join();

		for(int j=0; j<t; j++)	(*(r+id))+=comp[j];
	}
	
	for(int i=0; i<m; i++)	th[i] = thread(&f2_1,nu,(comp+i));
	for(int i=0; i<m; i++)	th[i].join();
	for(int i=0; i<m; i++)	(*(r+id))+=comp[i];

	delete comp;
}

void pr(ll *a, int t){
	for(int i=0; i<t; i++)	cout << *(a+i) << " ";
	cout << endl;
}

int main(int argc, char const *argv[]){
	int na = 100000, ft;
	cout << "first division: "; cin >> ft;
	int *a = new int[na];
	ll *r = new ll[na];
	ll *_r = new ll[na];
	for(int i=0; i<na; i++)	*(a+i) = i;
	int t = thread::hardware_concurrency();
	int div = ft/t;
	thread th[t];
	
	//1ft
	struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
	for(int i=0; i<div; i++){
		for(int j=0; j<t; j++)	th[j] = thread(&f1,*(a+(i*t)+j),((i*t)+j),r);
		for(int j=0; j<t; j++)	th[j].join();
	}
	gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time 1ft: %.8lf\n",tiempo/1000);
	
	int begin = div*t;
	// 2nd
    gettimeofday(&ti, NULL);
	for(int i=0; i<begin; i++)
		f2(*(a+i),i,_r);
	gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time 2nd: %.8lf\n",tiempo/1000);
	return 0;
}