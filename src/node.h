#ifndef _NODE_H_
#define _NODE_H_

#include <list>
#include <iostream>
using namespace std;

// -- nodo simple| lista simple
template<class T>
class lnode{
public:
	T m_dato;
	lnode<T> *m_next;
	lnode(T x){
		this->m_dato = x;
		this->m_next = NULL;
	}
};

// -- nodo doble | arbol, lista doble
template<class T>
class dnode{
public:
	T m_dato;
	dnode<T> *m_node[2];
    vector<unsigned> m_road;
	dnode(T x){
		this->m_dato = x;
		this->m_node[0] = this->m_node[1] = NULL;
	}
};

//arbol, m_road
template<class T>
class bnode{
public:
    T m_dato;
    bnode<T> *m_node[2];
    int m_balance, m_hight;
    vector<unsigned> m_road;
    bnode(T x){
        this->m_dato = x;
        this->m_node[0] = this->m_node[1] = NULL;
        this->m_balance = this->m_hight = 0;
    }
};

// -- nodo complex| grafo
template<class G>
class cnode{
public:
    typedef typename G::N 			N;
    typedef typename G::E           E;
    typedef typename G::edge 		edge;
    typedef typename G::node        node;
    typedef typename G::eiterator 	eiterator;
    unsigned m_id;
    unsigned m_pr;
    vector<unsigned> m_road;

    list<edge *> m_edges;
    E m_acum;
    N m_dato;

    cnode(N x, unsigned pos){ 
        this->m_dato = x;
        this->m_acum = 1<<12;
        this->m_id = pos;
    }

    bool operator==(node *&a){ //friend
        eiterator it, itr;
        for(it=m_edges.begin(); it!=m_edges.end(); it++){
            for(itr=a->m_edges.begin(); itr!=a->m_edges.end(); itr++)
                if(*it==*itr) return true;
        }   
        return false;
    }

    void print(){
        eiterator it;
        cout << "[" << this->m_id << "]|" << this->m_dato << ":\t";
        for(it=m_edges.begin(); it!=m_edges.end(); it++){
            if((*it)->m_nodes[1]->m_dato!=m_dato)   cout << "|" << (*it)->m_dato << "->" << (*it)->m_nodes[1]->m_dato << "\t";
            if((*it)->m_nodes[0]->m_dato!=m_dato)   cout << "|" << (*it)->m_dato << "->" << (*it)->m_nodes[0]->m_dato << "\t";
        }
        cout << endl;
    }
    
    void remove_edges(){
        edge *tm;
        while(!m_edges.empty()){
            tm = m_edges.front();
            ((tm->m_nodes[0])->m_edges).remove(tm);
            ((tm->m_nodes[1])->m_edges).remove(tm);
            delete tm;
        }
    }

    void remove_edge(cnode<G> *a){
    	eiterator it, itr;
    	for(it=m_edges.begin(); it!=m_edges.end(); it++){
    		for(itr=a->m_edges.begin(); itr!=a->m_edges.end(); itr++)
    			if(*it == *itr){
    				m_edges.remove(*it);
    				a->m_edges.remove(*itr);
                    delete *it;
    				return;
    			}
    	}	
    }
    ~cnode(){   };
};

#endif