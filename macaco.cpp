#include <iostream>
//#include <iomanip>
using namespace std;

extern "C" {
    
int SampleAddInt(int i1, int i2)    {
	return i1 + i2;
}

//int* type_test(char *str1,int id1,char *str2,float val,float *ls) {
//    int a = val;
//    return *a;
//}


struct Node {
    int data;
    Node *pChild[2];

    Node(int x):data(x) {
        pChild[0] = pChild[1] = nullptr;
    }
};

class BST {
protected:
    Node *pRoot;

public:
    BST():pRoot(nullptr) {}

    bool find(int x) {
        Node **p;
        return find(x, p);
    }

    void insert(int x) {
        Node **p;
        if (!find(x, p)) {
            *p = new Node(x);
        }
    }
    void remove(int x) {
        Node **p;
        if(find(x, p))
            remove(*p);
    }

    void print() {
        print(pRoot);
        cout << endl;
    }

private:
    bool find(int x, Node **&p) {
        p = &pRoot;
        while(*p) {
            if ((*p)->data==x) return true;
            p = &((*p)->pChild[(*p)->data < x]);
        }
        return false;
    }

    void remove(Node *&p) {
        if (!p->pChild[0] || !p->pChild[1])
            p = p->pChild[p->pChild[1]!=nullptr];
        else {
            Node **succesor = &(p->pChild[1]);
            find_min(succesor);
            p->data = (*succesor)->data;
            remove(*succesor);
        }
    }

    void find_min(Node **&p) {
        while((*p)->pChild[0]){
            p = &((*p)->pChild[0]);
        }
    }

    void print(Node *p, int indent=0) {
        if (p) {
            print(p->pChild[1], indent+6);
            //cout << setw(indent) << ' ';
            cout<< p->data <<endl;
            print(p->pChild[0], indent+6);
        }
    }
};

void dataframe(int array[], int size){ //similar to linspace from hw1
    for (int i = 0; i < size; i++){
        array[i]=1+10000*i;
    }}
 
double get_avg(int arr[], int size) {
  int i, sum = 0;       
  double avg;          
   for (i = 0; i < size; ++i) {
      sum += arr[i];
   }
   avg = double(sum) / size;
   cout << "Average value is: " << avg << endl; 
   return avg;
}
}
