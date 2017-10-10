#include <iostream>
#include "av.h"

int main(){
	avl_tree<int, int> avl;
	for(int i=0; i<1000000; i++)	avl.add(i, i);
}