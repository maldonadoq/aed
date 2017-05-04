#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
#include <stdio.h>

using namespace std;

template<class T>
class bnode{
public:
	T m_dato;
	bnode<T> *m_bnode[2];
	bnode(T x){
		this->m_bnode[0] = this->m_bnode[1] = NULL;
		this->m_dato = x;
	}
};

template<class T, class C>
class btree{
public:
	C cmp;
	bnode<T> *m_root;
//public:
	btree(){	this->m_root = NULL;	};
	bool find(T, bnode<T> **&);
	bool insert(T);
	bool remove(T);
	void rew(bnode<T> **&);
	void preorden(bnode<T> *);
	void inorden(bnode<T> *);
	void postorden(bnode<T> *);
	~btree(){	};
};

template<class T, class C>
bool btree<T,C>::find(T x, bnode<T> **&p){
	for(p=&(this->m_root); *p and ((*p)->m_dato!=x); p=&((*p)->m_bnode[cmp((*p)->m_dato,x)]));
	return !!*p;
}

template<class T, class C>
bool btree<T,C>::insert(T x){
	bnode<T> **p;
	if(find(x,p))	return 0;
	*p = new bnode<T>(x);
	return 1;
}

template<class T, class C>
void btree<T,C>::rew(bnode<T> **&q){
	for(q=&((*q)->m_bnode[1]); (*q)->m_bnode[0]!=NULL; q=&((*q)->m_bnode[0]));
}

template<class T, class C>
bool btree<T,C>::remove(T x){
	bnode<T> **p;
	if(!find(x,p))	return 0;
	if((*p)->m_bnode[0]!=NULL and (*p)->m_bnode[1]!=NULL){
		bnode<T> **q = p;
		rew(q);
		(*p)->m_dato = (*q)->m_dato;
		p = q;
	}
	bnode<T> *t = *p;
	*p = (*p)->m_bnode[(*p)->m_bnode[1]!=0];
	delete t;
	return 1;
}

template<class T, class C>
void btree<T,C>::preorden(bnode<T> *p){
	if(!p)	return;
	cout << p->m_dato << " ";
	preorden(p->m_bnode[0]);
	preorden(p->m_bnode[1]);
}

template<class T, class C>
void btree<T,C>::inorden(bnode<T> *p){
	if(!p)	return;
	inorden(p->m_bnode[0]);
	cout << p->m_dato << " ";
	inorden(p->m_bnode[1]);
}

template<class T, class C>
void btree<T,C>::postorden(bnode<T> *p){
	if(!p)	return;
	postorden(p->m_bnode[0]);
	postorden(p->m_bnode[1]);
	cout << p->m_dato << " ";
}

#endif