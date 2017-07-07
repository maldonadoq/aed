#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include "btree.h"

template<class T, class C>
class atree{
public:
	btree<int,C> *at;
	atree(){	this->at = new btree<int,C>();	}
	bool ins(T x){
		return at->insert(x.y);
	}
	bool rem(T x){
		return at->remove(x.y);
	}
	bool fin(T x){
		dnode<int> **p;
		return at->find(x.y,p);
	}
	~atree(){	};
};

template<class T>
class alist{
public:
	list<int> a;
	alist(){	};
	bool ins(T x){
		a.push_back(x.y);
		return true;
	}

	bool rem(T x){
		return a.remove(x.y);
	}

	bool fin(T x){
		typename list<int>::iterator it;
		for(it=a.begin(); it!=a.end(); it++)
			if((*it)==x.y)	return true;
		return false;
	}

	unsigned size(){	return a.size();	}
};

template<class T>
class avect{
public:
	vector<T> a;
	avect(){	};
	bool ins(T x){
		a.push_back(x);
		return true;
	}

	bool rem(T x){
		return true;
	}

	bool fin(T x){
		return false;
	}

	unsigned size(){	return a.size();	}
};

#endif