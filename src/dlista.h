#ifndef _DLISTA_H_
#define _DLISTA_H_

#include <iostream>
#include "cmp.h"
#include "node.h"

using namespace std;

template<class T, class C>
class dlista{
private:
	dnode<T> *m_head;
	dnode<T> *m_tail;
	C cmp;
public:
	dlista(){
		this->m_head = NULL;
		this->m_tail = NULL;
	}
	bool insert(T);
	bool remove(T);
	bool find(T,dnode<T> **&, dnode<T> *&);
	void print();
	void printr();
	~dlista();
};

template<class T, class C>
bool dlista<T,C>::find(T x, dnode<T> **&p, dnode<T> *&r){
	for(p=&(this->m_head), r=this->m_head; *p and cmp(x,(*p)->m_dato); r=*p, p=&((*p)->m_node[1]));
	return (*p and x==(*p)->m_dato);
}

template<class T, class C>
bool dlista<T,C>::insert(T x){
	dnode<T> **p, *r;
	if(find(x,p,r))	return false;
	dnode<T> *n = new dnode<T>(x), *t = *p;
	*p = n;
	n->m_node[1] = t;
	if(t){
		n->m_node[0] = t->m_node[0];
		t->m_node[0] = n;
		return true;
	}
	n->m_node[0] = r;
	this->m_tail = n;
	return true;
}

template<class T, class C>
bool dlista<T,C>::remove(T x){
	dnode<T> **p, *r;
	if(!find(x,p,r))	return false;
	dnode<T> *t = *p;
	*p = (*p)->m_node[1];
	if(*p){
		(*p)->m_node[0] = ((*p)->m_node[0])->m_node[0];
		delete t;
		return true;
	}
	this->m_tail = r;
	delete t;
	return true;
}

template<class T, class C>
void dlista<T,C>::print(){
	for(dnode<T> *tm=this->m_head; tm; tm=tm->m_node[1])
		cout << tm->m_dato << " ";
	cout << endl;
}

template<class T, class C>
void dlista<T,C>::printr(){
	for(dnode<T> *tm=this->m_tail; tm; tm=tm->m_node[0])
		cout << tm->m_dato << " ";
	cout << endl;
}

template<class T, class C>
dlista<T,C>::~dlista(){
	dnode<T> *t;
	while(this->m_head->m_node[1]){
		t = this->m_head ->m_node[1];
		this->m_head->m_node[1] = (this->m_head->m_node[1])->m_node[1];
		delete t;
	}
	delete m_head;
	delete m_tail;
}

#endif