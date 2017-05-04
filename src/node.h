#ifndef _NODE_H_
#define _NODE_H_

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

template<class T>
class dnode{
public:
	T m_dato;
	dnode<T> *m_node[2];
	dnode(T x){
		this->m_dato = x;
		this->m_node[0] = this->m_node[1] = NULL;
	}
};

#endif