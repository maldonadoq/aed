#ifndef _PREC_H_
#define _PREC_H_
#include "traits.h"

class con{
public:
	vector<unsigned> ve;
	con(vector<unsigned> _ve){
		this->ve = _ve;
	}
};

// no hash, un tipo de hash pero cambiado!!
template<class G>
class cprec{
public:
	typedef typename G::grafo	grafo;
	typedef typename G::N		N;
	typedef typename G::node 	node;
	typedef typename G::search	search;
	grafo *graph;
	vector<vector<N>> tab;
	vector<vector<con>> hash;
	search *a,*b,*c,*d;
	FILE *cal;
	cprec(grafo *a){
		this->graph = a;
		this->tab.resize(graph->m_prec.size());
		this->hash.resize(graph->m_prec.size());
		this->a = new search(graph);	this->b = new search(graph);
		this->c = new search(graph);	this->d = new search(graph);
	}
	void push(){
		unsigned i,k;
		node *tm;
		for(i=0; i<graph->m_nodes.size(); i++){
			tm = graph->m_nodes[i];	k=0;
			for(;!graph->ins(graph->m_prec[k],tm->m_dato) and k<graph->m_prec.size(); k++);
			tab[k].push_back(tm->m_dato);
		}
	}

	void calcular(){
		push();
		unsigned th = 4, tam = graph->m_prec.size();
		thread h[th];
		vector<unsigned> tp;
		for(unsigned i=0; i<tam; i++){
			if(tab[i].size()!=0)
				for(unsigned j=0; j<tam; j+=th){
					thread a1,b1,c1,d1;
					if(tab[j].size()!=0){	a1 = a->buscar(tab[i][0], tab[j][0]);	}
					if(tab[j+1].size()!=0){	b1 = b->buscar(tab[i][0], tab[j+1][0]);	}
					if(tab[j+2].size()!=0){	c1 = c->buscar(tab[i][0], tab[j+2][0]);	}
					if(tab[j+3].size()!=0){	d1 = d->buscar(tab[i][0], tab[j+3][0]); }
					
					if(tab[j].size()!=0){	a1.join();	hash[i].push_back(con(a->road));	}
					else hash[i].push_back(con(tp));
					
					if(tab[j+1].size()!=0){	b1.join();	hash[i].push_back(con(b->road));	}
					else hash[i].push_back(con(tp));
					
					if(tab[j+2].size()!=0){	c1.join();	hash[i].push_back(con(c->road));	}
					else hash[i].push_back(con(tp));

					if(tab[j+3].size()!=0){	d1.join();	hash[i].push_back(con(d->road));	}
					else hash[i].push_back(con(tp));				
				}
			else{
				hash[i].push_back(con(tp));
				hash[i].push_back(con(tp));
				hash[i].push_back(con(tp));
				hash[i].push_back(con(tp));
			}
		}
			/*for(unsigned j=0; j<tam; j+=th){
				thread a1 = a->buscar(tab[i][0], tab[j][0]);
				thread b1 = b->buscar(tab[i][0], tab[j+1][0]);
				thread c1 = c->buscar(tab[i][0], tab[j+2][0]);
				thread d1 = d->buscar(tab[i][0], tab[j+3][0]);
				a1.join();	b1.join();	c1.join();	d1.join();
				hash[i].push_back(a->road);
				hash[i].push_back(b->road);
				hash[i].push_back(c->road);
				hash[i].push_back(d->road);
			}
		*/
	}

	void save(){
		cal = fopen("../datos/calc.dat","w");
		unsigned tam = graph->m_prec.size();
		unsigned i1,j1;
		for(unsigned i=0; i<tam; i++){
			if(tab[i].size()!=0){
				graph->find(tab[i][0],i1);
				for(unsigned j = 0; j<tam; j++){
					graph->find(tab[i][j],j1);
					fprintf(cal,"%d %d\t",graph->m_nodes[i1]->m_pr,graph->m_nodes[j1]->m_pr);
					for(unsigned k=0; k<hash[i][j].ve.size(); k++)
						fprintf(cal,"%d ",hash[i][j].ve[k]);
					fprintf(cal,"%c",'\n');
				}
			}
		}
		fclose(cal);
	}

	~cprec(){	};
};

#endif