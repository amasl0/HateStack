#include "queue.h"
#include <iostream>

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
