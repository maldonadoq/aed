#ifndef _TRAITS_H_
#define _TRAITS_H_

#include "hash.h"
#include <iostream>
#include <math.h>
#include "node.h"

using namespace std;

template<class T>
class fdisp{
public:
	inline unsigned operator()(T a){
		return pow(a.x,2);
	}
};

template<class T>
class cuadr{
public:
    T a,d;
    cuadr(T _a, T _d){
        this->a = _a;
        this->d = _d;
    }
};

template<class _N, class _E, class _S>
class traits{
public:
    typedef traits<_N,_E,_S>	self;
    typedef _N				N;
    typedef _E				E;
    typedef _S				S;
    typedef cgrafo<self>	grafo;
    typedef cnode<self>		node;
    typedef cedge<self>		edge;
    typedef cuadr<N>        cuad;
    typedef chash<N,fdisp<N>,S,997> thash;
    typedef csearch<self,grafo> search;
    typedef typename list<node *>::iterator niterator;
    typedef typename list<edge *>::iterator eiterator;
};

class cord{
public:
    int x, y;
    cord(int _x=0, int _y=0){
        this->x = _x;
        this->y = _y;
    }
    friend bool operator==(const cord &a, const cord &b){
       	if(a.x == b.x && a.y == b.y) return true;
		return false;
   	}
   	friend bool operator!=(const cord &a, const cord &b){
       	if(a.x != b.x || a.y != b.y) return true;
		return false;
   	}
    friend ostream& operator<< (ostream & out, const cord &c){
       out << "(" << c.x << "," << c.y << ")";	
       return out;
   	}
   	double distance(cord a){
   		return sqrt(pow(this->x -a.x,2)+pow(this->y -a.y,2));
   	}
   	~cord(){	};
};

#endif