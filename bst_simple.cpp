#include <iostream>
//#include <cstdint>

//#include <iomanip>
using namespace std;

struct Node {
    int data;
    Node *pChild[2];

    Node(int x):data(x) {
        pChild[0] = pChild[1] = nullptr;
    }
};

class BST {
protected:
    //nothing
public:
    //template<typename ...Ts>
    //BST(Ts... ts);
    //
    //void process() {}
    //template <typename... Ts>
    //void process(int t, Ts... ts);
    
    Node *pRoot;
    
    BST():pRoot(nullptr) {}

    bool find(int x) {
        Node **p;
        return find_node(x, p);
    }
    
    bool find_node(int x, Node **&p) {
        p = &pRoot;
        cout << p << endl;
        while(*p) {
            if ((*p)->data==x) return true;
            p = &((*p)->pChild[(*p)->data < x]);
        }
        return false;
    }
    
    void insert(int x) {
        Node **p;
        if (!find_node(x, p)) {
            *p = new Node(x);
        }
    }

    void print() {
        print_nodes(pRoot);
        cout << endl;
    }

    void print_nodes(Node *p, int indent=0) {
        if (p) {
            print_nodes(p->pChild[1], indent+6);
            //cout << setw(indent) << ' ';
            cout<< p->data <<endl;
            print_nodes(p->pChild[0], indent+6);
        }
    }
private:
    //nothing 
};

// boost.python overloaded
// overloading: https://www.boost.org/doc/libs/1_68_0/libs/python/doc/html/tutorial/tutorial/functions.html#tutorial.functions.overloading

#include <boost/python.hpp>
using namespace boost::python;
BOOST_PYTHON_MODULE(macaco) {
    class_<BST>("BST", init<>())
        //.def(init<double, double>())
        .def("insert", &BST::insert)
        .def("find", &BST::find)
        .def("find_node", &BST::find_node)
        .def("print", &BST::print)
        .def("print_nodes", &BST::print_nodes)
        .def_readwrite("pRoot", &BST::pRoot)
    ;
    class_<Node>("Node", init<int>())
        .def_readwrite("data", &Node::data)
    ;
}

//template<typename ...Ts>
//BST::BST(Ts... ts): BST() {
//    process(ts...);
//}
//template <typename... Ts>
//void BST::process(int t, Ts... ts) {
//    BST::insert(t);
//    this->process(ts...);
//}

//BST(Ts... ts);
//void process()
//void process(int t, Ts... ts);

//int main() {
//    //BST bst(6,4,7,2,5,1,3); bst.print();
//    BST bst; bst.insert(6); bst.insert(4); bst.insert(9); bst.print();
//    cout << "-----------------\n";
//    cout << bst.pRoot << endl;
//    //uintptr_t p = 0xa41848;
//    //int value = *reinterpret_cast<int *>(p);
//    //cout << value << endl;
//    //bst.remove(4); bst.print();
//    return 0;
//}