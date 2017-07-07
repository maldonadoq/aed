#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <math.h>
#include "node.h"
#include "cmp.h"

using namespace std;

template<class T, class C>
class btree{
public:
	C cmp;
	bnode<T> *m_root;
	unsigned size;
//public:
	btree(){	this->m_root = NULL;	this->size = 0;	}
	bool find(T, bnode<T> **&);
	bool insert(T);
	bool remove(T);
	void rew(bnode<T> **&);
	void preorden(bnode<T> *);
	void inorden(bnode<T> *);
	void postorden(bnode<T> *);
	void bfs();
	~btree();
};

template<class T, class C>
bool btree<T,C>::find(T x, bnode<T> **&p){
	for(p=&(this->m_root); *p and ((*p)->m_dato!=x); p=&((*p)->m_node[cmp((*p)->m_dato,x)]));
	return !!*p;
}

template<class T, class C>
bool btree<T,C>::insert(T x){
	bnode<T> **p;
	if(find(x,p))	return false;
	*p = new bnode<T>(x);
	this->size++;
	return true;
}

template<class T, class C>
void btree<T,C>::rew(bnode<T> **&q){
	for(q=&((*q)->m_node[1]); (*q)->m_node[0]!=NULL; q=&((*q)->m_node[0]));
}

template<class T, class C>
bool btree<T,C>::remove(T x){
	bnode<T> **p;
	if(!find(x,p))	return false;
	if((*p)->m_node[0]!=NULL and (*p)->m_node[1]!=NULL){
		bnode<T> **q = p;
		rew(q);
		(*p)->m_dato = (*q)->m_dato;
		p = q;
	}
	bnode<T> *t = *p;
	*p = (*p)->m_node[(*p)->m_node[1]!=0];
	delete t;
	this->size--;
	return true;
}

template<class T, class C>
void btree<T,C>::preorden(bnode<T> *p){
	if(!p)	return;
	cout << p->m_dato << " ";
	preorden(p->m_node[0]);
	preorden(p->m_node[1]);
}

template<class T, class C>
void btree<T,C>::inorden(bnode<T> *p){
	if(!p)	return;
	inorden(p->m_node[0]);
	cout << p->m_dato << " ";
	inorden(p->m_node[1]);
}

template<class T, class C>
void btree<T,C>::postorden(bnode<T> *p){
	if(!p)	return;
	postorden(p->m_node[0]);
	postorden(p->m_node[1]);
	cout << p->m_dato << " ";
}

template<class T, class C>
void btree<T,C>::bfs(){
	queue<bnode<T> *> *a = new queue<bnode<T> *>();
	a->push(m_root);
	while(!a->empty()){
		cout << (a->front())->m_dato << " ";
		if((a->front())->m_node[0])	a->push((a->front())->m_node[0]);
		if((a->front())->m_node[1])	a->push((a->front())->m_node[1]);
		a->pop();
	}
	cout << endl;
	delete a;
}

template<class T, class C>
btree<T,C>::~btree(){
	queue<bnode<T> *> *a = new queue<bnode<T> *>();
	a->push(m_root);
	while(!a->empty()){
		if((a->front())->m_node[0])	a->push((a->front())->m_node[0]);
		if((a->front())->m_node[1])	a->push((a->front())->m_node[1]);
		delete a->front();
		a->pop();
	}
	delete a;
}

#endif