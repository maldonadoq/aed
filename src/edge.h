#ifndef _EDGE_H_
#define _EDGE_H_

// -- arista del nodo| grafo
template<class G>
class cedge{
public:
    typedef typename G::E E;
    typedef typename G::node node;
    node* m_nodes[2];
    E m_dato;
    bool m_dir;
    bool m_vst;
    cedge(E x, bool d){
        this->m_dato = x;
        this->m_dir = d;
        this->m_vst = false;
    }
    ~cedge(){   };
};

#endif