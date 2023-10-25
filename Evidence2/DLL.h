#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h
#include <string>
#include <stdexcept>
#include "DoubleNode.h"
#include "logE2.h"
#include <iostream>
template <class T>
class DoublyLinkedList {
    private:
        DNode<T>* head;
        DNode<T>* tail;
        int size = 0;
    public:
        DoublyLinkedList();
        void addFirst(T data);
        void addLast(T data);
        void print(std::string mode);
        void clear();
        void toArray(T* arr);
        int getSize(){return size;}
        T& operator[](int index);
        DNode<T>* getHead() const;
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(){
    head = nullptr;
    tail = nullptr;
}

template <class T>
DNode<T>* DoublyLinkedList<T>::getHead() const {
    return head;
}

template <class T>
void DoublyLinkedList<T>::addFirst(T data){
    head = new DNode<T>(data, head, nullptr);
    if (head->next == nullptr){
        tail = head;
    }
    else{
        head->next->prev = head;
    }
    size++;
}

template <class T>
void DoublyLinkedList<T>::addLast(T data){
    DNode<T>* newNode = new DNode<T>(data, nullptr, nullptr);
    
    if (head == nullptr) {
        // If the list is empty, set both head and tail to the new node
        head = newNode;
        tail = newNode;
    } else {
        // Otherwise, add the new node to the end of the list
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    
    size++;
}  

template <class T>
void DoublyLinkedList<T>::print(std::string mode){
    if(mode == "asc"){
        DNode<T>* aux = head;
        while (aux != nullptr){
            std::cout << aux->data << " ";
            if (aux->next != nullptr){
                std::cout << "=> ";
            }
            aux = aux->next;
        }
        std::cout << std::endl;
    }
    else {
        DNode<T>* aux = tail;
        while (aux != nullptr){
            std::cout << aux->data << " ";
            if (aux->prev != nullptr){
                std::cout << "=> ";
            }
            aux = aux->prev;
        }
        std::cout << std::endl;
    }
}

template <class T>
void DoublyLinkedList<T>::clear(){
    DNode<T>* aux = head;
    while (head != nullptr){
        head = head->next;
        delete aux;
        aux = head;
    }
    size = 0;
}

template <class T>
void DoublyLinkedList<T>::toArray(T* arr){
    DNode<T>* aux = head;
    int i = 0;
    while (aux != nullptr){
        arr[i] = aux->data;
        aux = aux->next;
        i++;
    }
}

template <class T>
T& DoublyLinkedList<T>::operator[](int index){
    if (index >= 0 && index < size){
        DNode<T>* aux;
        if (index <= (size - 1) / 2){
            int auxIndex = 0;
            aux = head;
            while (index != auxIndex){
                aux = aux->next;
                auxIndex++;
            }
        }
        else {
            int auxIndex = size - 1;
            aux = tail;
            while (auxIndex != index){
                aux = aux->prev;
                auxIndex--;
            }
        }
        return aux->data;
    } 
    else {
        throw std::out_of_range("Índice fuera de rango");
    }
}


#endif /* DoublyLinkedList_h */