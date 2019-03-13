#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "cmp.h"
#include "btree.h"
#include <thread>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

template<class G, class P>
class csearch{
public:
	typedef	typename G::grafo		grafo;
	typedef typename G::N			N;
	typedef typename G::eiterator	eiterator;
	typedef typename G::niterator	niterator;
	typedef typename G::node 		node;
	grafo *M;
	btree<unsigned,cml<unsigned>> *tree;
	N begin, end;
    unsigned i1,j1;
    vector<unsigned> road;
    string sws="";
    P *precalculo;
    bool exi;

    csearch(grafo *cr){  this->M = cr;   }
	csearch(grafo *cr, P *pr){    
        this->M = cr;
        this->precalculo = pr;
    }

	void f(bnode<unsigned> **&p, unsigned i, unsigned j){
        *p = new bnode<unsigned>(i);
        bnode<unsigned> **q;
        tree->find(j,q);
        (*p)->m_road = (*q)->m_road;
        (*p)->m_road.push_back(i);
    }

	void Thread(N a, N b){
		this->tree = new btree<unsigned,cml<unsigned>>();

		this->begin = a;
		this->end = b;

        struct timeval ti, tf;
        double tiempo;
        gettimeofday(&ti, NULL);
        if(!(this->M->find(this->begin,i1) and this->M->find(this->end,j1))){cout << "[ERROR: 404 NO POINT]" << endl; return; }
        prqueue<node, niterator> pq(this->M->m_nodes[j1]);
        pq.pushd(this->M->m_nodes[i1]);
        eiterator it;
        node *t;
        bnode<unsigned> **p;
        while(!pq.empty()){
            t = pq.top();   pq.pop();
            if(t==this->M->m_nodes[j1])    break;
            tree->insert(t->m_id);
            for(it=t->m_edges.begin(); it!=t->m_edges.end(); it++){
            	if((*it)->m_dir and !tree->find((*it)->m_nodes[0]->m_id,p)){	f(p,(*it)->m_nodes[0]->m_id,t->m_id);	pq.pushd((*it)->m_nodes[0]);	}
	            else if((*it)->m_dir and !tree->find((*it)->m_nodes[1]->m_id,p)){	f(p,(*it)->m_nodes[1]->m_id,t->m_id);	pq.pushd((*it)->m_nodes[1]);	}
            	else if(!tree->find((*it)->m_nodes[1]->m_id,p)){	f(p,(*it)->m_nodes[1]->m_id,t->m_id);	pq.pushd((*it)->m_nodes[1]);	}
            }
        }

        gettimeofday(&tf, NULL);
        tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
        vector<unsigned> sws;
        bnode<unsigned> **r;
        if(!tree->find(j1,r)){  
            this->exi=false; 
            this->road = sws; 
            //delete this->tree;
            return; 
        }
        cout << "[" << M->m_nodes[i1]->m_dato << "->" << M->m_nodes[j1]->m_dato << "]\t";
        printf("heuristic:  %.10f\t", tiempo/1000);
        this->exi=true;
        this->road = (*r)->m_road;
        cout << this->road.size() << endl;
    	delete this->tree;
    }

    void print(Vec3b col){
        if(!exi)    return;
        string r1=to_string(this->begin.x);
        string o1=to_string(this->begin.y);
        string a1=to_string(this->end.x);
        string d1=to_string(this->end.y);
        this->sws = "("+r1+","+o1+")->"+"("+a1+","+d1+")";
        
        namedWindow(this->sws, WINDOW_NORMAL); //window name 
        Mat src = M->map;

        line(src,Point(this->begin.x,this->begin.y),
        Point(M->m_nodes[road[0]]->m_dato.x,M->m_nodes[road[0]]->m_dato.y),
        col,1,4);
        for(unsigned i=0; i<this->road.size()-1; i++){
            line(src,Point(M->m_nodes[road[i]]->m_dato.x,M->m_nodes[road[i]]->m_dato.y),
                Point(M->m_nodes[road[i+1]]->m_dato.x,M->m_nodes[road[i+1]]->m_dato.y),
                col,1,4);
        }
        while(true){
            //setMouseCallback("My Window", CallBackFunc, NULL);
            //pyrUp(img, img, Size(img.cols * 2, img.rows * 2));
            imshow(this->sws,src); //show image store in img
            char key = (char)waitKey();
            if(key==27 || key=='q' || key =='Q')    break;
        }
        //imshow(this->sws,src); //show image store in img
        //waitKey(0);
        destroyWindow(this->sws);
    }

    thread buscar(N a, N b){
          return thread([=] { Thread(a,b); });
    }

	~csearch(){	};
};

#endif