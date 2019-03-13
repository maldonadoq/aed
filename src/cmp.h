#ifndef _CMP_H_
#define _CMP_H_

#include <iostream>

using namespace std;

//polimorfismo
template<class T>
class CP{
public:
	CP(){	};
	virtual bool cmp(T,T) = 0;
};

template<class T>
class F1 : public CP<T>{
public:
	F1(){	};
	bool cmp(T x, T y){	return x<y;	}
};

template<class T>
class F2 : public CP<T>{
public:
	F2(){	};
	bool cmp(T x, T y){	return x>y;	}
};


//puntero a funcion
template<class T>
bool gn(T x, T y){	return x<y;	}


//puntero a metodo
template<class T>
class fn{
public:
	fn(){	};
	bool f1(T x, T y){	return x<y;	}
	bool f2(T x, T y){	return x>y;	}
};
typedef bool (fn<int>::*ptr)(int, int);

//template - inline
template<class T>
class cmg{
public:
	inline bool operator()(T x, T y){	return x<y;	}
};

template<class T>
class cml{
public:
	inline bool operator()(T x, T y){	return x>y;	}
};

template<class T>
class cm{
public:
	inline bool operator()(T x, T y){	return x<=y;	}
};

void space(unsigned t){	for(unsigned i=0; i<t; i++)	cout << " ";	}

#endif