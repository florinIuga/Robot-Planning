// Copyright 2018 Iuga Florin

#ifndef STACK_H_

#define STACK_H_

#include <tuple>
template <typename T>
class Stack {
 private:
    T *stackArray;

    int maxCapacity;
    int resizeCapacity;
    int topLevel;

 public:
    Stack() {
        topLevel = -1;
        maxCapacity = 20;
        resizeCapacity = 2;
        stackArray =  new T[maxCapacity];
    }

    ~Stack() {
        delete[] stackArray;
    }

    void push(T element) {
        // check if the stack is full
        if (isFull()) {
            maxCapacity = maxCapacity*resizeCapacity;
            T *stackArrayCopy = new T[maxCapacity];
            for (int i = 0; i < maxCapacity/resizeCapacity; ++i)
            {
                stackArrayCopy[i] = stackArray[i];
            }
            delete[] stackArray;
            stackArray = stackArrayCopy;
        }

        topLevel++;
        stackArray[topLevel] = element;
    }

    void pop() {
        topLevel--;
    }

    T peek() {
        return stackArray[topLevel];
    }

    bool isEmpty() {
        if (topLevel != -1) return false;
        return true;
    }

    int size() {
        return topLevel + 1;
    }

    bool isFull() {
        if (topLevel == maxCapacity - 1) {
            return true;
        } else {
            return false;
        }
    }
};

#endif  // STACK_H_
