#ifndef _PRQUEUE_H_
#define _PRQUEUE_H_

#include <iostream>
#include <list>

template<class T, class nit>
class prqueue{
public:
	list<T *> a;
	T *end;
	prqueue(){	};
	prqueue(T *w){	this->end = w;	}

	void push(T* x){
		nit it = a.begin();
		for(; it!=a.end(); it++)
			if(x->m_acum<=(*it)->m_acum)	break;
		a.insert(it, x);
	}

	void pushd(T* x){
		nit it = a.begin();
		for(; it!=a.end(); it++)
			if(x->m_dato.distance(end->m_dato)<=(*it)->m_dato.distance(end->m_dato))	break;
		a.insert(it,x);
	}

	void pop(){	a.pop_front();	}

	T* top(){
		nit it = a.begin();
		return *it;
	}

	bool empty(){	return	a.empty();	}
};

#endif