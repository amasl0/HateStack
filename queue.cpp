//
// Created by donss on 31.07.2020.
//

#include <iostream>
#include <stdexcept>
#include <exception>
#include <ctime>
#include "queue.h"

// queue::public

void queue::push(int value) {
    size++; N_op += 2;
    node* new_node = new node(value); N_op += 4;
    if (tail == nullptr) {
        head = tail = new_node;
        return;
    }

    tail->prev = new_node;
    tail = new_node;
}

int queue::pop() {
    size--; N_op += 2;
    if (head == NULL)
        throw std::runtime_error("error");
    node* del_node = head;
    int data = head->data;
    head = head->prev;

    if (head == NULL) tail = NULL;

    delete del_node;
    return data;
}

int queue::get(int pos){
    checkPosition(pos);
    int result = 0; N_op+=1;
    for(int i = 1; i < pos; i++){
        push(pop());
    }
    result = head->data; N_op+=1;
    for(int i = size; i >= pos; i-- ){
        push(pop());
    }
    return result;
}

void queue::set(int pos, int value){
    checkPosition(pos);
    for(int i = 1; i < pos; i++){
        push(pop());
    }
    head->data = value; N_op+=1;
    for(int i = size; i >= pos; i-- ){
        push(pop());
    }
}

int queue::getSize() const{
    return size;
}

void queue::checkSize(){
    N_op+=1;
    if(size == 0)
        throw std::runtime_error("Stack is empty!");
}

void queue::checkPosition(int pos){
    N_op+=1;
    if(pos > size)
        throw std::runtime_error("Position larger than the size");
}

void queue::sort(){
    N_op = 0;
    start_time = clock();
    int index_i, index_j, index_k, index_g, startSize = size, exit_loop = 0, section = 1, step; N_op+=2;
    bool lock = false; N_op+=1;
    while(size != startSize * 2)
        push(0);
    do{

        section = 1 - section; N_op+=2;
        step = 1; N_op+=1;
        exit_loop = 1; N_op+=1;
        if(section == 0) {
            index_i = 1; N_op+=1;
            index_j = startSize; N_op+=1;
            index_k = startSize + 1; N_op+=2;
            index_g = startSize * 2; N_op+=2;
        } else {
            index_i = startSize + 1; N_op+=2;
            index_j = startSize * 2; N_op+=2;
            index_k = 1; N_op+=1;
            index_g = startSize; N_op+=1;
        }
        lock = true;
        for(int i = index_i + 1; i <= index_j; i++){
            if(get(i) < get(i - 1)){
                lock = false; N_op += 1;
                break;
            }

        }

        if(lock)
            break;
        while(index_i != index_j){
            if(get(index_i) > get(index_j)){
                set(index_k, get(index_j));
                index_k += step; N_op+=2;
                index_j--; N_op+=2;
            } else {
                set(index_k, get(index_i));
                index_i++; N_op+=2;
                index_k += step; N_op+=2;
            }
            do{
                if(index_i != 1 && index_i != startSize + 1){
                    if(get(index_i) < get(index_i - 1) || index_i == index_j)
                        break;
                }
                if(index_j != startSize && index_j != startSize * 2){
                    if(get(index_j) < get(index_j + 1) || index_i == index_j)
                        break;
                }
                if(get(index_i) > get(index_j)){
                    set(index_k, get(index_j));
                    index_k+=step; N_op+=2;
                    index_j--; N_op+=2;
                } else {
                    set(index_k, get(index_i));
                    index_k+=step; N_op+=2;
                    index_i++; N_op+=2;
                }
            } while(get(index_i) >= get(index_i - 1)  ||
                    get(index_j) <= get(index_j) ||
                    index_i != index_j);
            while(get(index_i) >= get(index_i - 1) && index_i != index_j){
                set(index_k, get(index_i));
                index_k += step; N_op+=2;
                index_i++; N_op+=2;
            }

            while(get(index_j) >= get(index_j + 1) && index_i != index_j){
                set(index_k, get(index_j));
                index_k += step; N_op+=2;
                index_j--; N_op+=2;
            }

            exit_loop = 0; N_op+=1;
            step *= -1; N_op+=2;
            int buffer = index_k; N_op+=1;
            index_k = index_g; N_op+=1;
            index_g = buffer; N_op+=1;
        }
        if(index_i == index_j)
            set(index_k, get(index_i));
    } while(exit_loop != 1);

    if(section == 1) {
        for (int i = 0; i < startSize; i++)
            pop();
    } else {
        for (int i = size; i > startSize; i--)
            push(pop());
        for (int i = 0; i < startSize; i++)
            pop();
    }

    end_time = clock();
}

