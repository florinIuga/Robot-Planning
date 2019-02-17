// Copyright 2018 Iuga Florin

#ifndef DEQUEUE_H_

#define DEQUEUE_H_

#include <tuple>


template <typename T>
struct Node {
  T comanda;
  Node<T> *next;
  Node<T>  *prev;

  explicit Node(T comanda) {
    this->comanda = comanda;
    next = NULL;
    prev = NULL;
  }
};

template <typename T>
class Dequeue {
 private:
  Node<T> *head;
  Node<T> *tail;
        int numElements;

 public:
  Dequeue(){
    head = NULL;
    tail = NULL;
                numElements = 0;
  }

    ~Dequeue(){
    freeTheQueue();  // eliberam memoria
  }

  // adaugarea la finalul cozii
  void addLast(T comanda) {
            Node<T> *newNode = new Node<T>(comanda);

            if (numElements == 0)
            {
                head = tail = newNode;

            } else {
      newNode->next = NULL;
      newNode->prev = tail;
                  tail->next = newNode;
      tail = newNode;
            }
            numElements++;
    }

    // adaugare la inceputul cozii
    void addFirst(T comanda) {
       Node<T> *newNode = new Node<T>(comanda);

      if (numElements == 0) {
        head = tail = newNode;

       } else {
       newNode->prev = NULL;
       newNode->next = head;
       head->prev =  newNode;
       head = newNode;
       }

      numElements++;
    }

    void removeFirst() {
        Node<T> *temp = head;
        if (numElements == 1) {
          head = NULL;
          tail = NULL;
        } else {
          head = temp->next;
          head->prev = NULL;
        }

  delete temp;
        numElements--;
    }

    void removeLast() {  // pentru UNDO  cand am prioritatea 1
        Node<T> *temp = tail;
        if (numElements == 1) {
          head = NULL;
          tail = NULL;
        } else {
        tail = temp->prev;
        tail->next = NULL;
        }
        delete temp;
        numElements--;
    }

    bool isEmpty() {
      if (numElements == 0) {
        return true;
      } else {
        return false;
      }
    }

    int size() {
      return numElements;
    }

    Node<T> *getHead() {
        return head;
    }

    Node<T> *getTail() {
        return tail;
    }

    void freeTheQueue() {
      Node<T> *temp;
      while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
      }
      numElements = 0;
    }
};

#endif  // DEQUEUE_H_
