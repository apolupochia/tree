#include <iostream>
using namespace std;

class Node;

template <typename T>
class List {
private:

    template <typename T1>
    class Node  {
    public:
        Node(string data,int key = 0,int a = 0,Node *pNext = nullptr){
            if ( a == -1){
                this->data = data;
                this->key = key;
                this->pNextLeft = nullptr;
                this->pNextRight = nullptr;
            }
            if ( a == 0){
                this->data = data;
                this->key = key;
                this->pNextLeft = pNext;
                this->pNextRight = nullptr;
            }
            if ( a == 1){
                this->data = data;
                this->key = key;
                this->pNextRight = pNext;
                this->pNextLeft = nullptr;
            }
        }

        string data;
        int key;
        Node *pNextRight;
        Node *pNextLeft;
        
    };
    
    
    int size;
    Node<T> *head;
    
    

    void outListRec(Node<T> *p );
    void balance();
    void balanceFunction(Node<T> *p ,int &count);
    void balanceChangePlace(int count, int a);
    void balanceLeft();
    void balanceRight();
    
public:
    
    List();
    ~List();
    void input(string data,int key);
    void outList();
    int getSize(){ return size; };
    void outElementForKey(int key);
    void deleteElement (int key);
    
};

template <typename T>
List<T>::List(){
    size = 0;
    head = nullptr;
}

template <typename T>
List<T>::~List(){
}


template <typename T>
void List<T>::input(string data,int key){
    if (size == 0){
        head = new Node<T> (data,key ,-1);
    }
    else{
        Node<T> *carrent = head;
        for(;;) {
            if (carrent->key > key){
                if (carrent->pNextLeft == nullptr){
                    carrent->pNextLeft = new Node<T>(data,key,0);
                    break;
                }
                carrent = carrent->pNextLeft;
            }
            if (carrent->key < key){
                if (carrent->pNextRight == nullptr){
                    carrent->pNextRight = new Node<T>(data,key,1);
                    break;
                }
                carrent = carrent->pNextRight;
            }
//            if (carrent->key == key){
//                if (carrent->pNextLeft == nullptr){
//                    carrent->pNextLeft = new Node<T>(data,key,0);
//                    break;
//                }
//                carrent = carrent->pNextLeft;
//            }
            if (carrent->key == key){
    
                char a = -1;
                while (1) {
                    cout << " this key is used,do you want change or leave?" << endl ;
                    cout << "enter: 0 - leave, 1 - change" << endl ;
                    cin >> a;
                    if(a == '0' || a == '1'){
                        break;
                    }
                }
                if (a == '1'){
                    carrent->data = data;
                }
                size--;
                break;
            }
        }
    }
    size++;
    balance();
}

template <typename T>
void List<T>::outListRec(Node<T> *p ){
    if(p->pNextLeft != nullptr){
        outListRec(p->pNextLeft);
    }
    cout << p->data << "  " << p->key << endl;
    
     if(p->pNextRight != nullptr){
        outListRec(p->pNextRight);
    }
}



template <typename T>
void List<T>::outList(){
    if (head == nullptr){
        cout << "Дерево пока пусто." << endl;
    }
    else{
        Node<T> *carrent = head;
        outListRec(carrent);
    }
}

template <typename T>
void List<T>::balanceFunction(Node<T> *p, int &count){
    if(p->pNextLeft != nullptr){
        balanceFunction(p->pNextLeft, count);
        count++;
    }
    
     if(p->pNextRight != nullptr){
         balanceFunction(p->pNextRight, count);
         count++;
    }
}




template <typename T>
void List<T>::balanceRight(){
    
    Node<T> *carrent = head;
    if(carrent->pNextRight != nullptr){
        carrent = carrent->pNextRight;
        if(carrent->pNextLeft != nullptr){
            while ((carrent->pNextLeft)->pNextLeft != nullptr) {
                carrent = carrent->pNextLeft;
            }
            Node<T> *head1;
            head1 = carrent->pNextLeft;
            head1->pNextRight =head->pNextRight;
            head->pNextRight = nullptr;
            head1->pNextLeft = head;
            carrent->pNextLeft = nullptr;
            head = head1;
        }
        else{
            Node<T> *head1;
            head1 = head->pNextRight;
            head->pNextRight = nullptr;
            head1->pNextLeft = head;
            head = head1;
        }
    }
}

template <typename T>
void List<T>::balanceLeft(){
    Node<T> *carrent = head;
    if(carrent->pNextLeft != nullptr){
        carrent = carrent->pNextLeft;
        if(carrent->pNextRight != nullptr){
            while (carrent->pNextRight != nullptr ) {
                if(carrent->pNextRight != nullptr){
                carrent = carrent->pNextRight;
                }
                else if (carrent->pNextLeft != nullptr){
                    carrent = carrent->pNextLeft;
                }
            }
            Node<T> *head1;
            head1 = carrent;
            head1->pNextRight = head;
            head1->pNextLeft = head->pNextLeft;
            (head1->pNextRight)->pNextLeft = nullptr;
            (head1->pNextLeft)->pNextRight = nullptr;
            head = head1;
            
        }
        else{
            Node<T> *head1;
            head1 = carrent;
            head1 ->pNextRight = head;
            (head1 ->pNextRight)->pNextLeft = nullptr;
            head = head1;
        }
    }
}

template <typename T>
void List<T>::balanceChangePlace( int count, int a){
    if (a == 1){
        balanceRight();
    }
    
    if (a == 0){
        balanceLeft();
    }
    
}

template <typename T>
void List<T>::balance(){
    
    Node<T> *carrent = head;
    
    int left = 0;
    int right = 0;
    
    if(carrent->pNextLeft != nullptr){
        left++;
        balanceFunction(carrent->pNextLeft, left);
    }
    if(carrent->pNextRight != nullptr){
        right++;
        balanceFunction(carrent->pNextRight, right);
    }
    
    if (left - right > 2){
        int k = left - right;
        //balanceChangePlace(k, 0);
    }
    if (right - left > 2){
        int k = right - left;
        //balanceChangePlace(k, 1);
    }
    
    cout << "Слева - " << left << "\tСправа - " << right << endl;
    
}

template <typename T>
void List<T>::outElementForKey(int key){
    Node<T> *carrent = head;
    if (head == nullptr) {
        cout << "Дерево пока пусто." << endl;
    }
    else if(carrent->key == key){
        cout <<"key = " << key << "\tdata = " << carrent->data <<  endl;
    }
    else {
        while (1) {
            if ((carrent->key > key) && (carrent->pNextLeft != nullptr)){
                carrent = carrent->pNextLeft;
            }
            else if ((carrent->key > key) && (carrent->pNextLeft == nullptr)){
                cout << "key not found" << endl;
                break;
            }
            if ((carrent->key < key) && (carrent->pNextRight != nullptr)){
                carrent = carrent->pNextRight;
            }
            else if ((carrent->key < key) && (carrent->pNextRight == nullptr)){
                cout << "key not found" << endl;
                break;
            }
            if (carrent->key == key){
                cout <<"key = " << key << "\tdata = " << carrent->data <<  endl;
                break;
            }
            if((carrent->pNextRight != nullptr) && (carrent->pNextLeft != nullptr)){
                cout << "key not found" << endl;
                break;
            }
        }
    }
        
}

template<typename T>
void List<T>::deleteElement(int key){
    Node<T> *carrent = head;
    Node<T> *carrent1 = head;
    if(head == nullptr){
        cout << "Дерево пока пусто." << endl;
    }
    else if(carrent->key == key){
        if((carrent->pNextRight == nullptr) && (carrent->pNextLeft != nullptr)){
            head = carrent->pNextLeft;
            delete carrent;
            size--;
        }
        else if ((carrent->pNextLeft == nullptr) && (carrent->pNextRight != nullptr)){
            head = carrent->pNextRight;
            delete carrent;
            size--;
        }
        else if ((carrent->pNextLeft == nullptr) && (carrent->pNextRight == nullptr)){
            delete head;
            size = 0;
            head = nullptr;
            size--;
        }
        else if ((carrent->pNextLeft != nullptr) && (carrent->pNextRight != nullptr)){
            if((carrent->pNextRight)->pNextLeft == nullptr){
                (carrent->pNextRight)->pNextLeft = head->pNextLeft;
                carrent = carrent->pNextRight;
                head->pNextLeft = nullptr;
                head->pNextRight = nullptr;
                delete head;
                head = carrent;
            }
            else if ((carrent->pNextRight)->pNextLeft != nullptr){
                carrent = carrent->pNextRight;
                while (carrent->pNextLeft != nullptr) {
                    carrent = carrent->pNextLeft;
                }
                carrent->pNextLeft = head->pNextLeft;
                carrent1= carrent1->pNextRight;
                head->pNextRight = nullptr;
                head->pNextLeft = nullptr;
                delete head;
                head = carrent1;
            }
            size--;
        }
            
    }
    else {
        while (1) {
            if ((carrent->key > key) && (carrent->pNextLeft != nullptr)){
                carrent1 = carrent;
                carrent = carrent->pNextLeft;
            }
            else if ((carrent->key > key) && (carrent->pNextLeft == nullptr)){
                cout << "key not found" << endl;
                break;
            }
            if ((carrent->key < key) && (carrent->pNextRight != nullptr)){
                carrent1 = carrent;
                carrent = carrent->pNextRight;
            }
            else if ((carrent->key < key) && (carrent->pNextRight == nullptr)){
                cout << "key not found" << endl;
                break;
            }
            
            
            if (carrent->key == key){
                
                
                if(carrent1->pNextLeft == carrent){
                    if((carrent->pNextLeft == nullptr) && (carrent->pNextRight == nullptr)){
                        carrent1->pNextLeft = nullptr;
                        delete  carrent;
                    }
                    if((carrent->pNextLeft == nullptr) && (carrent->pNextRight != nullptr)){
                        carrent1->pNextLeft = carrent->pNextRight;
                        delete carrent;
                    }
                    if((carrent->pNextLeft != nullptr) && (carrent->pNextRight == nullptr)){
                        carrent1->pNextLeft = carrent->pNextLeft;
                        delete carrent;
                    }
                    if((carrent->pNextLeft != nullptr) && (carrent->pNextRight != nullptr)){
                        Node<T> *carrent3 = carrent;
                        while (carrent3->pNextRight != nullptr) {
                            carrent3 = carrent3->pNextRight;
                        }
                        carrent3->pNextRight = carrent->pNextRight;
                        carrent->pNextRight = nullptr;
                        carrent1->pNextLeft = carrent->pNextLeft;
                        delete carrent;
                    }
                    break;
                    size--;
                }
                
                
                
                if(carrent1->pNextRight == carrent){
                    if((carrent->pNextLeft == nullptr) && (carrent->pNextRight == nullptr)){
                        carrent1->pNextRight = nullptr;
                        delete  carrent;
                    }
                    if((carrent->pNextLeft == nullptr) && (carrent->pNextRight != nullptr)){
                        carrent1->pNextRight= carrent->pNextRight;
                        delete carrent;
                    }
                    if((carrent->pNextLeft != nullptr) && (carrent->pNextRight == nullptr)){
                        carrent1->pNextRight = carrent->pNextLeft;
                        delete carrent;
                    }
                    if((carrent->pNextLeft != nullptr) && (carrent->pNextRight != nullptr)){
                        Node<T> *carrent3 = carrent;
                        carrent3 = carrent3->pNextLeft;
                        while (carrent3->pNextRight != nullptr) {
                            carrent3 = carrent3->pNextRight;
                        }
                        carrent3->pNextRight = carrent->pNextRight;
                        carrent->pNextRight = nullptr;
                        carrent1->pNextRight = carrent->pNextLeft;
                        delete carrent;
                    }
                    size --;
                    break;
                }
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    string a;
    int b,d;
    char input;
    List<char> A;
    
    while(1){
        cout << "Выберете действие: \n 1 - внести значения (строка(string) и ключ(int)) \n 2 - вывести количество всех элементов в дереве \n 3 - поиск по ключу (введите ключ(int)) \n 4 - удаление по ключу (введите ключ(int)) \n 5 - вывести все элементы" << endl;
        cin >> input;
        switch(input){
            case '1':
                cin >> a;
                cin >> b;
                A.input(a,b);
                break;
                
            case '2':
                d = A.getSize();
                cout << "SIZE = "  << d << endl;
                break;
                
            case '3':
                cin >> d;
                A.outElementForKey(d);
                break;
                
            case '4':
                cin >> d;
                A.deleteElement(d);
                break;
                
            case '5':
                A.outList();
                break;
                
            default:
                break;
        }
        
    }

    return 0;
}
