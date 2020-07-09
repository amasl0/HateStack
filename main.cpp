#include <iostream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <ctime>
#include <algorithm>

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

    void push(int value) {
        size++; N_op += 2;
        node* new_node = new node(value); N_op += 4;
        if (tail == nullptr) {
            head = tail = new_node;
            return;
        }

        tail->prev = new_node;
        tail = new_node;
    }
    int pop() {
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

    int get(int pos){
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
    void set(int pos, int value){ //!!
        checkPosition(pos);
        for(int i = 1; i < pos; i++){
            push(pop());
        }
        head->data = value; N_op+=1;
        for(int i = size; i >= pos; i-- ){
            push(pop());
        }
    }

    int getSize(){
        return size;
    }

    void checkSize(){
        N_op+=1;
        if(size == 0)
            throw std::runtime_error("Stack is empty!");
    }

    void checkPosition(int pos){
        N_op+=1;
        if(pos > size)
            throw std::runtime_error("Position larger than the size");
    }

    void sort(){
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
private:
    int size;
};

int main() {


    queue myqueue;

    myqueue.push(1);
    myqueue.push(8);
    myqueue.push(6);
    myqueue.push(8);
    myqueue.push(2);
    myqueue.push(8);
    myqueue.push(6);
    myqueue.push(5);
    myqueue.push(2);
    myqueue.push(10);
    myqueue.push(125);
    myqueue.push(112);
    myqueue.push(1);
    myqueue.sort();

    while(myqueue.getSize() != 0){
        std::cout << myqueue.pop() << std::endl;
    }

/*
    int N = 10;
    while (!(N > 500)) {
        queue myqueue;
        std::vector<int> x(N);
        for (int i = 0; i < N; i++) {
            x[i] = i; // инициализация диапозоном от 0 до N (здесь вы можете указать свой диапозон)
        }
        srand(unsigned(time(0)));
        std::random_shuffle(x.begin(), x.end()); // перемешиваеаем
        for (int i = 0; i < N; i++) {
            myqueue.push(x[i]);
        }
        myqueue.sort();
        std::cout << "Number of sorted items: " << N << "; Number of operation:" << myqueue.N_op
                  << "; Time to sort:" << (double) (myqueue.end_time - myqueue.start_time) / CLOCKS_PER_SEC
                  << " seconds;"
                  << std::endl;
        myqueue.start_time = 0;
        myqueue.end_time = 0;
        N*=2;
    }
    */
  /*
    queue myqueue;
    std::vector<int> x(50);
    for (int i = 0; i < 50; i++) {
        x[i] = i; // инициализация диапозоном от 0 до N (здесь вы можете указать свой диапозон)
    }
    srand(unsigned(time(0)));
    std::random_shuffle(x.begin(), x.end()); // перемешиваеаем
    for (int i = 0; i < 50; i++) {
        myqueue.push(x[i]);
    }
    myqueue.sort();
    while(myqueue.getSize() != 0){
        std::cout << myqueue.pop() << std::endl;
    }
    */
    return 0;
}
