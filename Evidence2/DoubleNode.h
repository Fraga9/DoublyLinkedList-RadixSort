#pragma once

template <class T>
struct DNode {
    T data;
    DNode<T>* next;
    DNode<T>* prev;
    DNode();
    DNode(T data);
    DNode(T data, DNode<T>* next, DNode<T>* prev);
};

template <class T>
DNode<T>::DNode(){
    next = nullptr;
    prev = nullptr;
}

template <class T>
DNode<T>::DNode(T data){
    this->data = data;
    next = nullptr;
    prev = nullptr;
    
}

template <class T>
DNode<T>::DNode(T data, DNode<T>* next, DNode<T>* prev){
    this->data = data;
    this->next = next;
    this->prev = prev;
}