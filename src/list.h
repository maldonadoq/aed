#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include "cmp.h"
#include "node.h"
#include <assert.h>
using namespace std;

template<class T, class C>
class list{
private:
	//CP<T> *m_cmp;
	//bool (*cmp)(T, T);
	/*fn<T> cmp;
	bool (fn<T>::*ptr)(T, T);*/
	C cmp;
	lnode<T> *m_head;
public:
		//polimorfismo
	//list(CP<T> *w){	this->m_cmp = w;	}
		//puntero a funcion
	//list(bool (*r)(T,T)){	this->cmp = r;	}
		//puntero a metodo
	//list(bool (fn<T>::*p)(T, T)){	this->ptr = p;	}
		//template
	list(){	this->m_head = NULL;	}
	bool find(T, lnode<T> **&);
	bool insert(T);
	bool remove(T);
	void print();
	~list();
};


template<class T, class C>
bool list<T,C>::find(T x, lnode<T> ** &p){
		//polimorfismo
	//for(p = &(this->m_head); *p and this->m_cmp->cmp(x,(*p)->m_dato); p = &((*p)->m_next) );
		//puntero a funcion
	//for(p = &(this->m_head); *p and cmp(x,(*p)->m_dato); p = &((*p)->m_next) );
		//puntero a metodo
	//for(p = &(this->m_head); *p and (cmp.*ptr)(x,(*p)->m_dato); p = &((*p)->m_next) );
		//template
	for(p = &(this->m_head); *p and cmp(x,(*p)->m_dato); p = &((*p)->m_next) );
	return (*p and x==(*p)->m_dato);
}

template<class T, class C>
bool list<T,C>::insert(T x){
	lnode<T> **p;
	if(find(x, p))	return false;
	lnode<T> *n = new lnode<T>(x);
	n->m_next = *p;
	*p = n;
	return true;
}

template<class T, class C>
bool list<T,C>::remove(T x){
	lnode<T> **p;
	if(!find(x, p))	return false;
	lnode<T> *t = *p;
	*p = (*p)->m_next;
	delete t;
	return true;
}

template<class T, class C>
void list<T,C>::print(){
	lnode<T> *t = this->m_head;
	assert(30<43);
	while(t){
		cout << t->m_dato << " ";
		t = t->m_next;
	}
	cout << endl;
}

template<class T, class C>
list<T,C>::~list(){
	lnode<T> *t;
	while(this->m_head){
		t = this->m_head;
		this->m_head = this->m_head->m_next;
		delete t;
	}
}

/*F2<int> r;
	CP<int> *p = &r;
	list<int> *a = new list<int>(p);
	puntero a funcion
	list<int> *a = new list<int>(gn);	
	puntero a metodo
	bool (fn<int>::*met)(int, int);
	met = &fn<int>::f1;
	list<int> *a = new list<int>(met);*/


#endif