#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "src/grafo.h"
#include "src/search.h"
#include "src/traits.h"
#include "src/allocator.h"
#include "src/cmp.h"
#include "src/sws.h"
#include "src/prec.h"
#include <thread>

using namespace std;

bool circle(cord *pt, cord p){
	return ((pow(p.x-pt[0].x,2)+pow(p.y-pt[0].y,2))<=pow(pt[1].x,2));
}

bool rectangle(cord *pt, cord p){
	return ((p.y>=pt[0].x and p.y<=pt[1].x) and (p.x<=pt[1].y and p.x>=pt[0].y));
}

//typedef traits<cord,int,alist<cord>> box;
typedef traits<cord,int,atree<cord,cml<int>>> box;
typedef cprec<box>	pre;

int main(int argc, char const *argv[]){
	cgrafo<box> *g = new cgrafo<box>();
	const unsigned px=2000;
	unsigned div = 20;
	
	//g->load(px,div);
	g->create(2500,px);
	cord rc[2] = {cord(400,750),cord(2000,1250)};
	g->obst(rectangle,rc);
	/*cord rc1[2] = {cord(10000,5000),cord(15000,15000)};
	g->obst(rectangle,rc1);
	cord cr[2] = {cord(250,250),cord(150,150)};
	g->obst(circle,cr);*/
	g->save(div);
	g->info();
	g->draw();
	
	Vec3b ca,cb,cc;
	ca[0]=255;	ca[1]=0;	ca[2]=0;
	cb[0]=0;	cb[1]=255;	cb[2]=0;
	cc[0]=255;	cc[1]=255;	cc[2]=255;
	pre *p = new pre(g);
	//p->push();
	//p->calcular();
	//p->save();
	
	csearch<box,pre> *a = new csearch<box,pre>(g,p);
	csearch<box,pre> *b = new csearch<box,pre>(g,p);
	csearch<box,pre> *c = new csearch<box,pre>(g,p);

	srand(time(NULL));
	unsigned siz = g->m_nodes.size();
	cord end = g->m_nodes[rand()%siz]->m_dato;
	thread a1 = a->buscar(g->m_nodes[rand()%siz]->m_dato,end);
	thread b1 = b->buscar(g->m_nodes[rand()%siz]->m_dato,end);
	thread c1 = c->buscar(g->m_nodes[rand()%siz]->m_dato,end);

	a1.join();	b1.join();	c1.join();
	a->print(ca);	b->print(cb);	c->print(cc);
    delete a;	delete b;	delete c;
    delete g;	delete p;	
    return 0;
}
//g++ -std=c++17 -pthread -Wall -DTEST --debug pr.cpp -lCGAL -lgmp -frounding-math
// 1000000 20000	cord rc[2] = {cord(400/2,750/2),cord(1600/2,1250/2)};