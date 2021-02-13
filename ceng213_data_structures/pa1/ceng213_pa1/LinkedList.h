#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"

template<class T>
class LinkedList{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    void insertAtTheHead(const T &data);
    void insertAtTheTail(const T &data);
    void insertSorted(const T &data);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();

    void print() const;

    T *toArray() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize){
    if(arrSize>=1){
        int index = 0;
        this->head = new Node<T>(arr[index++], nullptr, nullptr);
        Node<T> *current = this->head;
        while (index < arrSize){
            current->next = new Node<T>(arr[index++], current,nullptr);
            current = current->next;
        }
        this->tail = current;
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj){
    Node<T> *current = obj.head;
    if(current != nullptr){  
        Node<T> *element = new Node<T>(current->data, nullptr, nullptr);
        this->head = element;
        current = current->next;
        while (current != nullptr){
            element->next = new Node<T>(current->data, element, nullptr);
            element = element->next;
            current = current->next;
        }   
        this->tail = element;
    }
    else{
        this->head = nullptr;
        this->tail = nullptr;
    }
}

template<class T>
LinkedList<T>::~LinkedList(){
    Node<T> *pivot = this->head, *deleteNode= nullptr;
    while (pivot != nullptr){
        deleteNode = pivot;
        pivot = pivot->next;
        delete deleteNode;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const{
        return this->head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const{
        return this->tail;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const{
    if(!isEmpty()){
        Node<T> *current;
        current = this->head;
        while(current != nullptr){
            if(current->data==data){
                return current;
            }
            current = current -> next;
        }
    }
    return nullptr;
}

template<class T>
int LinkedList<T>::getNumberOfNodes() const{
    int num = 0;
    Node<T> *current;
    current = this->head;
    while(current!=nullptr){
        num++;
        current = current->next;
    }
    return num;
}

template<class T>
bool LinkedList<T>::isEmpty() const{
    return ((this->head == nullptr) && (this->tail == nullptr));               
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const{
    if(!isEmpty()){
        Node<T> *current;
        current = this->head;
        while(current != nullptr){
            if ((node->data == current->data) && (node->prev == current->prev) && (node->next == current->next)){
                return true;
            }  
            current = current -> next;
        }
    }
    return false;
}

template<class T>
void LinkedList<T>::insertAtTheHead(const T &data){
    Node<T> *element = new Node<T>(data, nullptr, this->head);
    if (!isEmpty()){
        this->head->prev = element;
    }
    else{
        this->tail = element;
    }
    this->head = element;
    
}

template<class T>
void LinkedList<T>::insertAtTheTail(const T &data){
    Node<T> *element = new Node<T>(data, this->tail, nullptr);
    if(!isEmpty()){
        this->tail->next = element;
    }
    else{
        this->head = element;
    }
    this->tail = element;

}

template<class T>
void LinkedList<T>::insertSorted(const T &data){
    if (!isEmpty()){
        if (data < this->head->data){
            insertAtTheHead(data);
        }
        else if (this->tail->data < data){
            insertAtTheTail(data);
        }
        else{
            Node<T> *current = this->head, *element = new Node<T>(data, nullptr, nullptr);
            while (current->next != nullptr){
                if (data < current->next->data){
                    element->next = current->next;
                    element->prev = current;
                    current->next = element;
                    element->next->prev = element;
                    current = nullptr;
                    element = nullptr;
                    delete current;
                    delete element;
                    return;
                }
                current = current -> next;
            }
        }
    }
    else{
        Node<T> *element = new Node<T>(data, nullptr, nullptr);
        this->head = element;
        this->tail = element;
    }

}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node){
    if(!isEmpty()){
        Node<T> *current;
        current = this->head;
        if ((node->data == current->data) && (node->prev == current->prev) && (node->next == current->next)){
            if(this->head == this->tail){
                this->head = this->tail = nullptr;
            }
            else{
                this->head = current->next;
                this->head->prev = nullptr;
            }
        
            delete current;
            return;
        }
        while(current != this->tail){
            if ((node->data == current->data) && (node->prev == current->prev) && (node->next == current->next)){
                if(current->next != nullptr){
                    current->next->prev = current->prev;
                    }
                if (current->prev != nullptr){
                    current->prev->next = current->next;
                }
                delete current;
                return;
            }  
            current = current -> next;
        }
        if ((node->data == current->data) && (node->prev == current->prev) && (node->next == current->next)){
            if(this->head == this->tail){
                this->head = this->tail = nullptr;
            }
            else{
                this->tail = current->prev;
                this->tail->next = nullptr;
            }
            delete current;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data){
    Node<T> *del_node = getNode(data);
    if(del_node != nullptr){
        removeNode(del_node);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes(){
    Node<T> *pivot = this->head, *nextThisNode = nullptr;
    while (pivot != nullptr){
        nextThisNode = pivot->next;
        removeNode(pivot);
        pivot = nextThisNode;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

template<class T>
void LinkedList<T>::print() const{
    std::cout << "Printing the linked list ..." << std::endl;
    if (this->isEmpty()){
        std::cout << "empty" << std::endl;
    }

    Node<T> *node = this->head;
    while (node){
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
T *LinkedList<T>::toArray() const{/* TODO */ //array sonunu belirten eleman gerekli mi sor???
    if(!isEmpty()){
        int range = getNumberOfNodes(), index = 0;
        T *arr = new T[range];
        Node<T> *current;
        current = this->head;
        while(index < range){
            arr[index++] = current->data;
            current = current -> next;
        }
        return arr;
    }
    return nullptr;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs){
    Node<T> *pivot = rhs.head;
    this->removeAllNodes();

    while (pivot!= nullptr){
        this->insertAtTheTail(pivot->data);
        pivot = pivot->next;
    } 
    return *this;
}
#endif //LINKEDLIST_H
