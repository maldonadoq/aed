#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <list>
#include <queue>
#include <vector>
#include <unistd.h>
#include <sys/time.h>
#include <algorithm>
#include <stdlib.h>
#include "node.h"
#include "edge.h"
#include "btree.h"
#include "prqueue.h"

using namespace std;
using namespace cv;

FILE *word;

template<class G>
class cgrafo{
public:
    typedef typename G::N           N;
    typedef typename G::E           E;
    typedef typename G::node        node;
    typedef typename G::edge        edge;
    typedef typename G::niterator   niterator;
    typedef typename G::eiterator   eiterator;
    typedef typename G::cuad        cuad;
    unsigned ne, nn, px;
    vector<node *> m_nodes;
    vector<cuad> m_prec;
    FILE *nod, *edg, *tri, *pre;
    Mat map;
    string name;
    cgrafo(){
        this->ne = 0; 
        this->nn = 0;   
        this->name = "Perú";
    }
    void info(){
        cout << "-----------------------------------------" << endl;
        cout << "   nodos: " << m_nodes.size() << "    aristas: " << ne << endl;
        cout << "-----------------------------------------" << endl;  
    }

    bool find(N x, unsigned &i){
        for(i=0; i<m_nodes.size(); i++)
            if(m_nodes[i]->m_dato==x)	return true;
        return false;
    }
    
    bool insert_node(N x){
        node *tr = new node(x,nn++);
        m_nodes.push_back(tr);
        return true;
    }
    
    // crear un grafo aleatorio, para unir nodos
    bool insert_edge_al(E x, node *a, node *b, bool d){
        edge *c = new edge(x,d);
        a->m_edges.push_back(c);
        b->m_edges.push_back(c);
        c->m_nodes[0] = a;
        c->m_nodes[1] = b;
        this->ne++;
        return true;
    }

    // unir nodos, yo les doy el nodo
    bool insert_edge(E x, N a, N b, bool d){
        unsigned p,q;
        if(find(a,p) and find(b,q)){
            edge *c = new edge(x,d);
            m_nodes[p]->m_edges.push_back(c);
            m_nodes[q]->m_edges.push_back(c);
            c->m_nodes[0] = m_nodes[p];
            c->m_nodes[1] = m_nodes[q];
        }
        this->ne++;
        return true;
    }
    
    bool remove_edge(N a, N b){
    	unsigned p,q;
    	if(!(find(a,p) and find(b,q)))	return false;
    	m_nodes[p]->remove_edge(m_nodes[q]);
    	this->ne--;
        return true;
    }
    
    bool remove_node(N x){
        unsigned p;
        if(!find(x,p))   return false;
        this->ne -= m_nodes[p]->m_edges.size();
        m_nodes[p]->remove_edges();
        delete m_nodes[p];
        m_nodes.erase(m_nodes.begin()+p);
        this->nn--;
        return true;
    }
    
    void print(){
    	info();
        unsigned wq = (m_nodes.size()/10 == 0)? 1: m_nodes.size()/10;
        for(unsigned i=0; i<m_nodes.size(); i+=wq)  
            m_nodes[i]->print();
    }

    void draw(){
        this->map = Mat(this->px,this->px,CV_8UC3,Scalar(0,0,0));
        for(unsigned i=0; i<m_nodes.size(); i++){
            for(eiterator it=m_nodes[i]->m_edges.begin();it!=m_nodes[i]->m_edges.end();it++){
                if((*it)->m_nodes[1]->m_dato!=m_nodes[i]->m_dato)
                    line(map,Point(m_nodes[i]->m_dato.x,m_nodes[i]->m_dato.y),
                    Point(m_nodes[(*it)->m_nodes[1]->m_id]->m_dato.x,m_nodes[(*it)->m_nodes[1]->m_id]->m_dato.y),
                    Scalar(0,0,255),1,4);   
            }
        }
        namedWindow(name, WINDOW_NORMAL); //window name 
        while(true){
            imshow(name,this->map); //show image store in img
            char key = (char)waitKey();
            if(key==27 || key=='q' || key =='Q')    break;
        }
        destroyWindow(name);
    }

    void city(){
        string im="city";
        namedWindow(im, WINDOW_NORMAL); //window name 
        Mat src(this->px, this->px, CV_8UC3, Scalar(255,255,255));
        Vec3b cl;
        cl[0] = 0; cl[1] = 0;   cl[2] = 255;
        for(unsigned i=0; i<m_nodes.size();i++){
            src.at<Vec3b>(m_nodes[i]->m_dato.x,m_nodes[i]->m_dato.y) = cl;
        }
        imshow(im,src); //show image store in img
        waitKey(0);
        destroyWindow(im);
    }

    void obst(bool (*pt)(N *, N),N *punt){
        N tm;
        for(unsigned i=0; i<m_nodes.size(); i++){
            tm = m_nodes[i]->m_dato;
            if(pt(punt,tm)){
                remove_node(m_nodes[i]->m_dato);
                i--;
            }
        }
        for(unsigned i=0; i<m_nodes.size(); i++)    m_nodes[i]->m_id = i;
    }
    
    bool ins(cuad cu, N p){
        return ((p.y>=cu.a.x and p.y<=cu.d.x) and (p.x<=cu.d.y and p.x>=cu.a.y));
    }

    void create(unsigned np, unsigned _px){
        this->px = _px;
        nod = fopen("../datos/node.dat","w");
        srand(time(NULL));
        bool **mr = new bool*[px];
        for(unsigned i=0; i<px; i++){
            mr[i] = new bool[px];
            for(unsigned j=0; j<px; j++)    mr[i][j] = false;
        }
        while(nn<np){
            N qr(rand()%px,rand()%px);
            if(!mr[qr.x][qr.y]){
                mr[qr.x][qr.y] = true;
                insert_node(qr);
                fprintf(nod,"%d\t%d\n",qr.x, qr.y);
            }
        }
        cout << endl;
        fclose(nod);
        
        for(unsigned i=0; i<px; i++)    delete mr[i];
        delete [] mr;
        system("g++ -std=c++17 -pthread triangulation.cpp -o trian");
        system("./trian");

        tri = fopen("../datos/trian.dat","r");
        edg = fopen("../datos/edge.dat","w");
        string n1="",n2="",n3="";
        int con = 0,i,j,k,w1,w2,w3,d1,d2,d3;
        char c;
        while((c=getc(tri))!=EOF){
            if(con==0){
                if(c!='\t') n1+=c;
                else    con++;
            }
            else if(con==1){
                if(c!='\t') n2+=c;
                else    con++;
            }
            else{    
                if(c!='\n') n3+=c;
                else if(c=='\t') continue;
                else{
                    con = 0;
                    w1 = (rand()%20)+1; w2 = (rand()%20)+1; w3 = (rand()%20)+1;
                    d1 = rand()%2; d2 = rand()%2; d3 = rand()%2;
                    i = stoi(n1)-1;   j = stoi(n3)-1;   k = stoi(n2)-1;
                    if(!m_nodes[i]->operator==(m_nodes[j])){
                        insert_edge_al(w1, m_nodes[i],m_nodes[j],d1);
                        fprintf(edg, "%d\t%d\t%d\t%d\n",w1,i,j,d1);
                    }
                    if(!m_nodes[i]->operator==(m_nodes[k])){
                        insert_edge_al(w2, m_nodes[i],m_nodes[k],d2);
                        fprintf(edg, "%d\t%d\t%d\t%d\n",w2,i,k,d2);
                    }
                    if(!m_nodes[j]->operator==(m_nodes[k])){
                        insert_edge_al(w3, m_nodes[j],m_nodes[k],d3);
                        fprintf(edg, "%d\t%d\t%d\t%d\n",w3,j,k,d3);
                    }
                    n1=n2=n3="";
                }
            }
        }
        fclose(edg);
        fclose(tri);
    }

    void save(unsigned fr){
        nod = fopen("../datos/node.dat","w");
        edg = fopen("../datos/edge.dat","w");
        pre = fopen("../datos/prec.dat","w");
        eiterator it;
        node *tm;

        unsigned cel = px/fr,kw;
        for(unsigned i=0; i<px; i+=cel)
            for(unsigned j=0; j<px; j+=cel)
                m_prec.push_back(cuad(N(i,j),N(i+cel,j+cel)));

        for(unsigned i=0; i<m_nodes.size(); i++){
            tm = m_nodes[i];
            kw = 0;
            for(;!ins(m_prec[kw],tm->m_dato) and kw<m_prec.size(); kw++);
            m_nodes[i]->m_pr = kw;
            fprintf(pre,"%d\t",kw);
            fprintf(nod,"%d\t%d\n",tm->m_dato.x, tm->m_dato.y);
            for(it=tm->m_edges.begin(); it!=tm->m_edges.end(); it++)
                if((*it)->m_nodes[1]->m_dato!=tm->m_dato)
                    fprintf(edg, "%d\t%d\t%d\t%d\n",(*it)->m_dato,tm->m_id,(*it)->m_nodes[1]->m_id,(*it)->m_dir);
        }

        fclose(pre);
        fclose(edg);
        fclose(nod);
    }

    void load(unsigned _px, unsigned fr){
        this->px = _px;

        unsigned cel = px/fr;
        for(unsigned i=0; i<px; i+=cel)
            for(unsigned j=0; j<px; j+=cel)
                m_prec.push_back(cuad(N(i,j),N(i+cel,j+cel)));

        nod = fopen("../datos/node.dat","r");
        char c;
        string n1="",n2="",n3="",n4="";
        int con=0,i,j;
        while((c=getc(nod))!=EOF){
            if(con==0){
                if(c!='\t') n1+=c;
                else    con++;
            }
            else{
                if(c!='\n') n2+=c;
                else{
                    con = 0;
                    i = stoi(n1);   j = stoi(n2);
                    insert_node(N(i,j));
                    n1=n2="";
                }
            }
        }
        fclose(nod);

        edg = fopen("../datos/edge.dat","r");
        n1=n2=n3="";
        con = 0;
        while((c=getc(edg))!=EOF){
            if(con==0){
                if(c!='\t') n1+=c;
                else    con++;
            }
            else if(con==1){
                if(c!='\t') n2+=c;
                else    con++;
            }
            else if(con==2){
                if(c!='\t') n3+=c;
                else    con++;
            }
            else{    
                if(c!='\n') n4+=c;
                else{
                    con = 0;
                    insert_edge_al(stoi(n1), m_nodes[stoi(n2)],m_nodes[stoi(n3)],stoi(n4));
                    n1=n2=n3=n4="";
                }
            }
        }
        fclose(edg);

        /*pre = fopen("../datos/prec.dat","r");
        n1="";
        con = 0;
        while((c=getc(edg))!=EOF){
            if(c!='\t') n1+=c;
            else{
                m_nodes[con]->m_pr = stoi(n1);
                n1="";  con++;
            }
        }
        fclose(pre);*/
    }

    virtual ~cgrafo(){ 
        unsigned t = m_nodes.size(), i;
        for(i=0; i<t; i++)  delete m_nodes[i];
    }
};

#endif