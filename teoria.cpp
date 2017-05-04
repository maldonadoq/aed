#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <thread>

FILE *a, *b, *c, *d;

using namespace std;

class CP{
public:
	CP(){	};
	virtual bool cmp(int,int) = 0;
};

class F1 : public CP{
public:
	F1(){	};
	bool cmp(int x, int y){	return x<y;	}
};

class F2 : public CP{
public:
	F2(){	};
	bool cmp(int x, int y){	return x>y;	}
};

class cm{
public:
	inline bool operator()(int x, int y){	return x<y;	}
};

void swap1(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

bool compare(int a, int b){	return a<b;	}

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

void quick1(int *a,int izq, int der, bool (*p)(int, int)){ 
    int i, j, x; 
    i = izq; 
    j = der; 
    x = *(a + (izq+der)/2); 
    do{ 
        while(p(*(a+i),x) and (j<=der))    i++;
        while(p(x,*(a+j)) and (j>izq)) j--;
 
        if(i<=j){ 
            swap1((a+i), (a+j));
            i++;  j--; 
        }
         
    }while(i<=j);
    
    if(izq<j)  quick1(a, izq, j,p); 
    if(i<der)  quick1(a, i, der,p);
}

void quick2(int *a,int izq, int der, CP *w){ 
    int i, j, x; 
    i = izq; 
    j = der; 
    x = *(a + (izq+der)/2); 
    do{ 
        while(w->cmp(*(a+i),x) and (j<=der))    i++;
        while(w->cmp(x,*(a+j)) and (j>izq)) j--;
 
        if(i<=j){ 
            swap1((a+i), (a+j));
            i++;  j--; 
        }
         
    }while(i<=j);
    
    if(izq<j)  quick2(a, izq, j, w); 
    if(i<der)  quick2(a, i, der, w);
}

template<class C>
void quick3(int *a, int izq, int der){
	C w; 
	int i, j, x; 
    i = izq; 
    j = der; 
    x = *(a + (izq+der)/2); 
    do{ 
        while(w(*(a+i),x) and (j<=der))    i++;
        while(w(x,*(a+j)) and (j>izq)) j--;
 
        if(i<=j){ 
            swap1((a+i), (a+j));
            i++;  j--; 
        }
         
    }while(i<=j);
    
    if(izq<j)  quick3<cm>(a, izq, j); 
    if(i<der)  quick3<cm>(a, i, der);	
}

void pull(int *a, int *b, int *c, int *d, int t){
	int temp;
	for(int i=0; i<t; i++){
		temp = rand()%t;
		*(a+i) = temp;
		*(b+i) = temp;
		*(c+i) = temp;
		*(d+i) = temp;
	}
}

void dat_0(FILE *a, int *A, int t, void (*p)(int *, int, int)){
	double tim;
	struct timeval ti, tf;
    gettimeofday(&ti, NULL);
    p(A, 0, t-1);
    gettimeofday(&tf, NULL);
    tim = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;

	fprintf(a, "%d\t", t);
	fprintf(a, "%lf\n", tim);
}

void dat_1(FILE *a, int *A, int t, bool (*c)(int, int), void (*p)(int *, int, int, bool (*)(int, int))){
	double tim;
	struct timeval ti, tf;
    gettimeofday(&ti, NULL);
    p(A, 0, t-1, c);
    gettimeofday(&tf, NULL);
    tim = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;

	fprintf(a, "%d\t", t);
	fprintf(a, "%lf\n", tim);
}

void dat_2(FILE *a, int *A, int t, CP *w, void (*p)(int *, int, int, CP *)){
	double tim;
	struct timeval ti, tf;
    gettimeofday(&ti, NULL);

    p(A, 0, t-1, w);

    gettimeofday(&tf, NULL);
    tim = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;

	fprintf(a, "%d\t", t);
	fprintf(a, "%lf\n", tim);
}

void dat_3(FILE *a, int *A, int t, void (*p)(int *, int, int)){
	double tim;
	struct timeval ti, tf;
    gettimeofday(&ti, NULL);
    p(A, 0, t-1);

    gettimeofday(&tf, NULL);
    tim = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;

	fprintf(a, "%d\t", t);
	fprintf(a, "%lf\n", tim);
}

int main(int argc, char const *argv[]){
	int t;
	unsigned r;

	a = fopen("../datos/quick_normal.dat", "w");
	b = fopen("../datos/quick_puntero.dat", "w");
	c = fopen("../datos/quick_polimorfismo.dat", "w");
	d = fopen("../datos/quick_template.dat", "w");

	//cout << "pruebas: "; cin >> t;
	t = 100;
	r = 100;

	F2 qw;
	CP *po = &qw;

	for(int i=0; i<t; i++, r+=10000){
		int *A = new int[r];
		int *B = new int[r];
		int *C = new int[r];
		int *D = new int[r];
		pull(A,B,C, D,r);
		dat_0(a, A, r, quick);
		dat_1(b, B, r, compare, quick1);
		dat_2(c, C, r, po, quick2);
		dat_3(d, D, r, quick3<cm>);
		delete A; delete B; delete C; delete D;
	}

	fclose(a);
	fclose(b);
	fclose(c);
	fclose(d);

	return 0;
}

//valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes ./a.out
//kcachegrind callgrind.out.$pid
    //7976 -O1
    //8140 -O2
    //8335 -O3
//plot "quick_normal.dat" w l, "quick_puntero.dat" w l, "quick_polimorfismo.dat" w l, "quick_template.dat" w l