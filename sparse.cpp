#include <iostream>
#include <stdio.h>

using namespace std;

template<class T, T n>
class spm;

template<class R>
class cnode{
public:
	R m_dato;
	unsigned x,y;
	cnode<R> *m_right, *m_down;
	cnode(unsigned _x, unsigned _y, R _d){
		this->m_dato = _d;
		this->x = _x;	this->y = _y;
		this->m_right = this->m_down = NULL;
	}
};

template<class T, T n>
class sparse{
public:
	typedef cnode<T>	node;

	node **right, **down;
	unsigned xs,ys;
	
	sparse(){	};
	sparse(unsigned _x, unsigned _y){	
		this->xs = _x;
		this->ys = _y;
		this->right = new node*[this->xs];
		this->down = new node*[this->ys];
	}

	bool find(unsigned _x, unsigned _y, node **&p, node **&q){
		for(p = &(this->right[_x]);*p and (*p)->y!=_y; p=&((*p)->m_down));
		for(q = &(this->down[_y]);*q and (*q)->x!=_x; q=&((*q)->m_right));
		return !!(*p);
	}

	void insert(unsigned _x, unsigned _y,T _d,node **&p, node **&q){
		node *ne = new node(_x,_y,_d);
		ne->m_down = *p;
		ne->m_right = *q;
		*p = ne;
		*q = ne;
	}

	bool remov(node **&p, node **&q){
		node *t = *p;
		*p = (*p)->m_down;
		*q = (*q)->m_right;
		delete t;
		return true;
	}

	void lista(){
		node *p, *q;
		for(unsigned i=0; i<xs-1; i++){
			p = right[i];
			if(p){
				q = p;
				while(q->m_down){
					//cout << q->m_dato << " ";
					q = q->m_down;
				}
				q->m_down = right[i+1];
			}
		}

		node *tmp = right[0];
		while(tmp){
			cout << tmp->m_dato << " ";
			tmp->m_right = NULL;
			tmp = tmp->m_down;
		}
		cout << endl;

		delete []this->right;
		delete []this->down;
	}

	spm<T,n> operator()(unsigned _x, unsigned _y){
		if(!(_x<xs and _y<ys)) throw;
		return spm<T,n>(_x,_y,this);
	}

	sparse<T,n> operator*(sparse<T,n> &b){
		if(this->xs != b.ys)	return sparse<T,n>(0,0);
		unsigned xst = this->ys, yst = b.xs;
		sparse<T,n> c(xst,yst);
		T tmp = 0;
		for(unsigned i=0; i<yst; i++){
	        for(unsigned j=0; j<xst; j++){
	            for(unsigned z=0; z<b.ys; z++)
	                tmp += (*this)(z,j) * b(i,z);
	            c(j,i) = tmp; 
	            tmp = 0;
	        }
	    }

	    c.print();
		return c;
	}

	void set(unsigned _x, unsigned _y, T d){
		cnode<T> **p,**q;
		find(_x,_y,p,q);
		if(!(*p) and d==n)	return;
		else if(d == n)	remov(p,q);
		else if((*p))	(*p)->m_dato=d;
		else	insert(_x,_y,d,p,q);
	}

	T get(unsigned i, unsigned j){
		node **p,**q;
		find(i,j,p,q);
		if(*p)	return (*p)->m_dato;
		else	return n;
	}

	void print(){
		cout << "m[" << this->xs << "][" << this->ys << "]" << endl;
		for(unsigned i=0; i<ys; i++){
			for(unsigned j=0; j<xs; j++)
				cout << get(j,i) << " ";
			cout << endl;
		}
		cout << endl;
	}

	~sparse(){
		delete this->right;
		delete this->down;
	}
};

template<class T, T n>
class spm{
public:
	int x, y;
	sparse<T,n> *m;
	spm(unsigned _x, unsigned _y, sparse<T,n> *a){
		this->x = _x;	this->y = _y;
		this->m = a;
	}
	void operator=(T d){	m->set(this->x, this->y, d);	}

	void operator=(spm<T,n> c){	m->set(this->x, this->y, m->get(c.x,c.y));	}
	
	operator T(){	return m->get(this->x, this->y);	}

	ostream& operator<<(ostream & out){
       out << m->get(this->x, this->y);;
       return out;
   	}
};

typedef sparse<int,0> spars;
int main(int argc, char const *argv[]){
	spars a(2,2);
	//insert
	a(0,0) = 0;		a(0,1) = 1;
	a(1,0) = 2;		a(1,1) = 3;
	a.print();
	a.lista();



	return 0;
}