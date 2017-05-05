#ifndef _CLISTA_H_
#define _CLISTA_H_

#include <iostream>
#include "node.h"

using namespace std;

template<class T, class C>
class clista{
private: 
	C cmp;
	lnode<T> *m_head;
	lnode<T> *m_tail;
public:
	clista(){	
		this->m_head = NULL;
		this->m_tail = NULL;
	}
	bool find(T, lnode<T> **&);
	bool insert(T);
	bool remove(T);
	void print();
	~clista();
};

template<class T, class C>
bool clista<T,C>::find(T x, lnode<T> **&p){
	p = &(m_head);
	if(m_tail)	m_tail->m_next = NULL; //la suelto!!
	while(*p and cmp(x,(*p)->m_dato)){
		p = &((*p)->m_next);
	}
	return (*p and x==(*p)->m_dato);
}

template<class T, class C>
bool clista<T,C>::insert(T x){
	lnode<T> **p;
	if(find(x,p)){
		m_tail->m_next = m_head;
		return false;
	}
	lnode<T> *n = new lnode<T>(x);
	lnode<T> *t = *p;
	n->m_next = t;
	*p = n;
	if(!t)	m_tail=n;
	m_tail->m_next = m_head;
	return true;
}

template<class T, class C>
void clista<T,C>::print(){
	if(!m_head)	return;
	lnode<T> *t=m_head;
	do{
		cout << t->m_dato << " ";
		t=t->m_next;
	}while(t!=m_head);
	cout << endl;
}

template<class T, class C>
clista<T,C>::~clista(){
	m_tail->m_next = NULL;
	lnode<T> *t;
	while(this->m_head){
		t = this->m_head;
		this->m_head = this->m_head->m_next;
		delete t;
	}
}

#endif