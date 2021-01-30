//
// Created by donss on 2.05.2020.
//
#pragma once
#include <ctime>

class queue {
public:
    clock_t start_time;
    clock_t end_time;
    long long N_op;

    class node{
    public:
        int data;
        node* prev;
        node* next;
        node(int value){
            data = value; // N_op += 1
            prev = nullptr; // N_op += 1
            next = nullptr;// N_op += 1
        }
    };

    node* head = nullptr;
    node* tail = nullptr;

    queue(){
        head = nullptr; N_op+=1;
        tail = nullptr; N_op+=1;
        size = 0; N_op+=1;
    };

    void push(int value);
    int pop();

    int get(int pos);
    void set(int pos, int value);

    int getSize() const;

    void checkSize();

    void checkPosition(int pos);

    void sort();
private:
    int size;
};

