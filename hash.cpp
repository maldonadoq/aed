#include <iostream>
#include "src/hash.h"
#include "src/cmp.h"
#include "src/btree.h"
#include <math.h>
#include <list>

using namespace std;

template<class T>
class fdisp{
public:
	inline unsigned operator()(T a){
		return pow(a,2);
	}
};

template<class T, class C>
class atree{
public:
	btree<T,C> *at;
	atree(){	this->at = new btree<T,C>();	}
	bool ins(T x){
		return at->insert(x);
	}
	bool rem(T x){
		return at->remove(x);
	}
	bool fin(T x){
		bnode<T> **p;
		return at->find(x,p);
	}
	unsigned size(){
		return at->size;
	}
	void pri(){
		at->inorden(this->at->m_root);
	}
	~atree(){	};
};

//2039
const unsigned r=10;
typedef chash<int,fdisp<int>,atree<int,cml<int>>,r> _hash;

int main(int argc, char const *argv[]){
	FILE *nu = fopen("../datos/nu.dat","w");
	fprintf(nu,"%d\t%d\n",0,0);
	fprintf(nu,"%d\t%d\n",r,0);
	fclose(nu);


	_hash *a = new _hash();
	unsigned t=30;
	srand(time(NULL));

	for(unsigned i=0; i<t; i++)	a->insert(i);
	cout << a->find(3) << endl;
	cout << a->find(4) << endl;
	cout << a->remove(3) << endl;
	cout << a->remove(3) << endl;

	FILE *da = fopen("../datos/hash.dat","w");
	for(unsigned i=0; i<r; i++)	fprintf(da,"%d\t%d\n",i,a->m_table[i].size());
	fclose(da);
	
	for(unsigned i=0; i<r; i++){
		cout << "m_table[" << i << "]:\t";
		a->print(i);
	}

	return 0;
	
}