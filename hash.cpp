#include <iostream>
#include <stdio.h>
#include "../func/func.cpp"

using namespace std;

class t_hash{
public:
	int *m_a;
	int m_t;
	t_hash(int t){
		this->m_t = t;
		this->m_a = new int[this->m_t];
	}

	void f_hash(int *v){
		for(int i=0; i<this->m_t; i++){
			int ind = modulo1(*(v+i), this->m_t);
			while(*(m_a+ind)!=0){
				ind++;
				ind = modulo1(ind, this->m_t);
			}
			*(m_a+ind) = *(v+i);
		}
	}

	void print(){
		for(int i=0; i<this->m_t; i++)	cout << *(m_a + i) << " ";
		cout << endl;
	}

	int buscar(int d){
		int ind = modulo1(d, this->m_t), c = 0;
		//bool t=true;
		while(*(m_a + ind)!=0){
			if(*(m_a + ind) == d)	return ind;
			//ind++;
			ind = modulo1(ind++, this->m_t);
			c++;
			if(c>this->m_t)	return -1;
		}
		return -1;
	}

	~t_hash(){	};
	
};

int main(int argc, char const *argv[]){
	int t = 8;
	int *s = new int[t];
	
	/*srand(time(NULL));
	for(int i=0; i<t; i++){
		*(s+i) = rand()%100;
	}*/
	
	*(s+0) = 20; *(s+1) = 33; *(s+2) = 21; *(s+3) = 10;
	*(s+4) = 12; *(s+5) = 14; *(s+6) = 56; *(s+7) = 100;

	t_hash *h = new t_hash(t);
	h->f_hash(s);
	h->print();
	cout << h->buscar(20) << endl;
	cout << h->buscar(56) << endl;
	cout << h->buscar(12) << endl;
	cout << h->buscar(200) << endl;
	cout << h->buscar(33) << endl;
	cout << h->buscar(14) << endl;
	cout << h->buscar(21) << endl;
	cout << h->buscar(10) << endl;

	return 0;
}