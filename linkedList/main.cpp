#include <iostream>
#include <string>

using namespace std;

template <typename T>
class List{
private:
    class Node{
    public:
        Node *pNext;
        T data;
        Node(T data=T(), Node *pNext=nullptr){
            this->data = data;
            this->pNext = pNext;
        }
    };

    int Size;
    Node *head;

    void CheckOutOfRange(const int index){
        if (index >= Size || index < 0){
            throw out_of_range("Index out of range");
        }
    }
    void SearchPreviousElement(Node *& previous, const int index){
        for (int i = 0; i < index - 1; i++){
            previous = previous->pNext;
        }
    }
public:
    List();
    ~List();
    void push_back(T data);
    void pop_back();
    void pop_front();
    void insert(T data, const int index);
    void push_front(T data);
    void removeAt(const int index);
    void clear();
    int size(){ return Size; }
    T& operator[](const int index);

};
template <typename T>
List<T>::List(){
    Size = 0;
    head = nullptr;
}
template <typename T>
List<T>::~List(){
    clear();   
}
template <typename T>
void List<T>::push_back(T data){
    if (head != nullptr){
        Node *current = head;
        while(current->pNext != nullptr){
            current = current->pNext;
        }
        current->pNext = new Node(data);
    } else { 
        head = new Node(data); 
    }
    Size++;
}
template <typename T>
void List<T>::pop_front(){
    if (head != nullptr) {
        Node *temp = head;
        head = head->pNext;
        delete temp;
        Size--;
    }
}
template <typename T>
void List<T>::clear(){
    while (Size){
        pop_front();
    }
}
template <typename T>
void List<T>::push_front(T data){
    head = new Node(data, head);
    Size++;
}
template <typename T>
T &List<T>::operator[](const int index)
{
    CheckOutOfRange(index);

    int counter = 0;
    Node *current = head;
    while(current != nullptr){
        if (counter == index){
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}
template <typename T>
void List<T>::pop_back(){
    removeAt(Size - 1);
}
template <typename T>
void List<T>::insert(T data, const int index)
{
    CheckOutOfRange(index);

    if (index == 0){
        push_front(data);
    } else if (index == Size - 1){
        push_back(data);
    } else {
        Node *previous = head;
        SearchPreviousElement(previous, index);

        Node *newNode = new Node(data, previous->pNext);
        previous->pNext = newNode;
        Size++;
    }
}

template <typename T>
void List<T>::removeAt(const int index){
    CheckOutOfRange(index);

    if (index == 0){
        pop_front();
    } else {
        Node *previous = head;
        SearchPreviousElement(previous, index);

        Node *toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;
        Size--;
    }
}

int main(){
    
    srand(time(nullptr));
    List<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.pop_front();
    lst.push_front(100);
    lst.insert(1000, lst.size() - 1);
    lst.insert(20, 2);
    lst.removeAt(1);
    lst.pop_back();
    lst.clear();
    
    return 0;
}

