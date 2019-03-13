#ifndef _LISTA_H_
#define _LISTA_H_

#include "cmp.h"
#include "node.h"

using namespace std;

template<class T, class C>
class lista{
private:
	lnode<T> *m_first;
	C cmp;
public:
	lista();
	bool find(T, lnode<T> **&);
	bool insert(T);
	bool remove(T);
	bool swap_b(lnode<T> **&, lnode<T> **&);
	bool swap_i(lnode<T> **&, lnode<T> **&);
	void bubble_sort();
	void insertion_sort();
	void print();
	~lista();
};

template<class T, class C>
lista<T,C>::lista(){
	this->m_first = NULL;
}

template<class T, class C>
bool lista<T,C>::insert(T x){
	lnode<T> **p = &(this->m_first);
	lnode<T> *t = *p;
	*p = new lnode<T>(x);
	(*p)->m_next = t;
	return 1;
}

template<class T, class C>
bool lista<T,C>::find(T x, lnode<T> **&p){
	for(p=&(this->m_first); *p and (*p)->m_dato!=x; p=&((*p)->m_next));
	return *p;
}

template<class T, class C>
bool lista<T,C>::remove(T x){
	lnode<T> **p;
	if(!find(x,p))	return false;
	lnode<T> *t = *p;
	*p = (*p)->m_next;
	delete t;
	return true;
}

template<class T, class C>
bool lista<T,C>::swap_b(lnode<T> **&p, lnode<T> **&r){
	//print();
	if(p==r)	return false;
	lnode<T> *w = *p;
	*p = *r;
	*r = (*p)->m_next;
	(*p)->m_next = w;
	return true;
}

template<class T, class C>
void lista<T,C>::bubble_sort(){
	lnode<T> **p, **q, **r;
	for(p=&(this->m_first); (*p)->m_next; p=&((*p)->m_next)){
		for(r=p, q=&((*p)->m_next); *q; q=&((*q)->m_next)){
			if(cmp((*q)->m_dato,(*r)->m_dato))	r = q;
		}
		swap_b(p,r);
	}
}

template<class T,class C>
bool lista<T,C>::swap_i(lnode<T> **&p, lnode<T> **&r){
	//print();
	if(p==r)	return false;
	lnode<T> *q = *p;
	*p = (*p)->m_next;
	q->m_next = *r;
	*r = q;
	return true;
}

template<class T, class C>
void lista<T,C>::insertion_sort(){
	lnode<T> **p, **r;
	p=&(this->m_first);
	while(*p){
		r = &(this->m_first);
		while(cmp((*r)->m_dato,(*p)->m_dato) and r!=p){
			r=&((*r)->m_next);
		}
		if(!swap_i(p,r))	p=&((*p)->m_next);
	}
}

template<class T, class C>
void lista<T,C>::print(){
	lnode<T> *tmp = this->m_first;
	while(tmp){
		cout << tmp->m_dato << " ";
		tmp = tmp->m_next;
	}
	cout << endl;
}	

template<class T, class C>
lista<T,C>::~lista(){
	lnode<T> *t;
	while(this->m_first){
		t = this->m_first;
		this->m_first = this->m_first->m_next;
		delete t;
	}
}

#endif