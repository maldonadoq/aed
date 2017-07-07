#ifndef _AVL_H_
#define _AVL_H_

#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <math.h>
#include "node.h"
#include "cmp.h"

using namespace std;

template<class T, class C>
class avl{
public:
	C cmp;
	bnode<T> *m_root;
	unsigned size;
	stack<bnode<T>**> m_bal;
//public:
	avl(){	this->m_root = NULL;	this->size = 0;	}
	bool find(T, bnode<T> **&);
	bool insert(T);
	bool remove(T);
	void rew(bnode<T> **&);
	void preorden(bnode<T> *);
	void inorden(bnode<T> *);
	void postorden(bnode<T> *);
	void bfs();
	int hight(bnode<T> *);
	void balance();
	void RR(bnode<T> **&);
	void LL(bnode<T> **&);
	void RL(bnode<T> **&);
	void LR(bnode<T> **&);
	void print();
	~avl();
};

template<class T, class C>
int avl<T,C>::hight(bnode<T> *a){
  if (!a)	return 0;
  return max(hight(a->m_node[0]),hight(a->m_node[1]))+1;
}

template<class T, class C>
void avl<T,C>::balance(){
	bnode<T> **tmp;
	while(!this->m_bal.empty()){
		tmp = this->m_bal.top();	this->m_bal.pop();
		(*tmp)->m_balance = hight((*tmp)->m_node[1])-hight((*tmp)->m_node[0]);
		
		if((*tmp)->m_balance==2 and (*tmp)->m_node[1]->m_balance==-1)	LR(tmp);
		else if((*tmp)->m_balance==-2 and (*tmp)->m_node[0]->m_balance==1)	RL(tmp);
		else if((*tmp)->m_balance==2)	RR(tmp);
		else if((*tmp)->m_balance==-2)	LL(tmp);
	}
}

template<class T, class C>
void avl<T,C>::RR(bnode<T> **&p){
	bnode<T> *tmp = *p;
	*p = (*p)->m_node[1];
	tmp->m_node[1] = (*p)->m_node[0];
	(*p)->m_node[0] = tmp;
}

template<class T, class C>
void avl<T,C>::LL(bnode<T> **&p){
	bnode<T> *tmp = *p;
	*p = (*p)->m_node[0];
	tmp->m_node[0] = (*p)->m_node[1];
	(*p)->m_node[1] = tmp;
}

template<class T, class C>
void avl<T,C>::RL(bnode<T> **&p){
	bnode<T> **tmp = &((*p)->m_node[0]);
	RR(tmp);
	LL(p);
}

template<class T, class C>
void avl<T,C>::LR(bnode<T> **&p){
	bnode<T> **tmp = &((*p)->m_node[1]);
	LL(tmp);
	RR(p);
}

template<class T, class C>
bool avl<T,C>::find(T x, bnode<T> **&p){
	this->m_bal = stack<bnode<T> **>{};
	for(p=&(this->m_root); *p and ((*p)->m_dato!=x); p=&((*p)->m_node[cmp((*p)->m_dato,x)]))	this->m_bal.push(p);
	return !!*p;
}

template<class T, class C>
bool avl<T,C>::insert(T x){
	bnode<T> **p;
	if(find(x,p))	return false;
	*p = new bnode<T>(x);
	this->size++;
	balance();
	cout << "insert: " << x << endl;
	print();
	return true;
}

template<class T, class C>
void avl<T,C>::rew(bnode<T> **&q){
	for(q=&((*q)->m_node[1]); (*q)->m_node[0]!=NULL; q=&((*q)->m_node[0]));
}

template<class T, class C>
bool avl<T,C>::remove(T x){
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
	balance();
	cout << "remove: " << x << endl;
	print();
	return true;
}

template<class T, class C>
void avl<T,C>::preorden(bnode<T> *p){
	if(!p)	return;
	cout << p->m_dato << " ";
	preorden(p->m_node[0]);
	preorden(p->m_node[1]);
}

template<class T, class C>
void avl<T,C>::inorden(bnode<T> *p){
	if(!p)	return;
	inorden(p->m_node[0]);
	cout << p->m_dato << " ";
	inorden(p->m_node[1]);
}

template<class T, class C>
void avl<T,C>::postorden(bnode<T> *p){
	if(!p)	return;
	postorden(p->m_node[0]);
	postorden(p->m_node[1]);
	cout << p->m_dato << " ";
}

template<class T, class C>
void avl<T,C>::bfs(){
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
void avl<T, C>::print(){

	vector<bnode<T>*> node;
	vector<int> niveles;
	vector<T> cont;
	int nivel=1;
	int ind=0;
	vector<bnode<T>*> temp1;
	node.push_back(this->m_root);
	cont.push_back(this->m_root->m_dato);
	niveles.push_back(nivel);
	do{
		vector<bnode<T>*> temp;
		for (unsigned i = ind; i < node.size(); ++i){
			if(node[i]->m_node[0]!=NULL){
				temp.push_back(node[i]->m_node[0]);
				cont.push_back(node[i]->m_node[0]->m_dato);
			}
			else	cont.push_back(-9999);
			if(node[i]->m_node[1]!=NULL){
				temp.push_back(node[i]->m_node[1]);
				cont.push_back(node[i]->m_node[1]->m_dato);
			}
			else	cont.push_back(-9999);
		}

		if (nivel>1 && temp.size()<pow(2,nivel-1)){
			for (int i = 0; i < pow(2,nivel-1)-temp.size(); ++i)	cont.push_back(-9999);
		}

		ind = node.size();
		nivel++;
		for (unsigned i = 0; i < temp.size(); ++i){
			node.push_back(temp[i]);
			niveles.push_back(nivel);
		}
		temp1=temp;
	}while(temp1.size()!=0);
	vector<T> conte;
	for(unsigned i=0; i<(pow(2,hight(m_root))-1); i++)	conte.push_back(cont[i]);

	int nu = conte.size();
    int lw = pow(2,(int)(log2(nu))+3);
    int print_pos[nu];
    int i, j, k, pos, x=1, level=0;

    print_pos[0] = 0;
    //(pow(2,level+1) ancho
    for(i=0,j=1; i<nu; i++,j++) {
        pos = print_pos[(i-1)/2] + (i%2?-1:1)*(lw/(pow(2,level+1))+1);
        for (k=0; k<pos-x; k++) printf("%c",i==0||i%2?' ':'-');
        (conte[i]==-9999)?printf("%c",'n'):printf("%d",conte[i]);

        print_pos[i] = x = pos+1;
        if (j==pow(2,level)) {
            printf("\n\n");
            level++;
            x = 1;
            j = 0;
        }
    }
    cout << endl;
}                        

template<class T, class C>
avl<T,C>::~avl(){
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