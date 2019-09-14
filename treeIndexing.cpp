#include <iostream>
#include <vector>
#include <string>
#include <set>

#include <iomanip>
#include <initializer_list>
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>

using namespace std;

//START OF HEADER
template<typename Tnodes>
struct Node {
    Tnodes data;
    std::set<int> rows;

    Node *pChild[2];
    Node(Tnodes x):data(x) {
        pChild[0] = pChild[1] = nullptr;
    }
};

template<typename Ttrees>
class treeIndexing {
public:
	Node<Ttrees> *pRoot;
    treeIndexing():pRoot(nullptr) {}

    bool find_node(Ttrees x) {
        Node<Ttrees> **p;
        return find(x, p);
    }

    void remove(Ttrees x) {
        Node<Ttrees> **p;
        if(find(x, p))
            remove(*p);
    }

    void print() {
        print(pRoot);
        cout << endl;
    }

    std::set<int> locateRow(Ttrees nd) {
        Node<Ttrees> **p;
        find(nd, p);
        return (*p)->rows;
    }

    void insertRow(Ttrees nd, int row) {
        Node<Ttrees> **p;
        if (!find(nd, p)) {
            *p = new Node<Ttrees>(nd);
        }
        (*p)->rows.insert(row);
    }

    void insertNode(Ttrees nd) {
        Node<Ttrees> **p;
        if (!find(nd, p)) {
            *p = new Node<Ttrees>(nd);
        }
    }
private:
    bool find(Ttrees x, Node<Ttrees> **&p) {
        p = &pRoot;
        while(*p) {
            if ((*p)->data==x) return true;

            p = &((*p)->pChild[(*p)->data < x]);
        }

        return false;
    }

    void remove(Node<Ttrees> *&p) {
        if (!p->pChild[0] || !p->pChild[1])
            p = p->pChild[p->pChild[1]!=nullptr];

        else {
            Node<Ttrees> **succesor = &(p->pChild[1]);
            find_min(succesor);
            p->data = (*succesor)->data;
            remove(*succesor);
        }
    }

    void find_min(Node<Ttrees> **&p) {

        while((*p)->pChild[0]){
            p = &((*p)->pChild[0]);
        }
    }
	
	void print(Node<Ttrees> *p, int indent=0) {
	        if (p) {
	            print(p->pChild[1], indent+6);
	            cout << setw(indent) << ' ';
	            cout<< p->data <<endl;
	            print(p->pChild[0], indent+6);
	        }
	}
};

//END OF HEADER


//template<typename Ttrees>
//void treeIndexing::print(Node<Ttrees> *p, int indent=0) {
//        if (p) {
//            print(p->pChild[1], indent+6);
//            cout << setw(indent) << ' ';
//            cout<< p->data <<endl;
//            print(p->pChild[0], indent+6);
//        }
//}