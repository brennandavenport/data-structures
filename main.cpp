#include "vector.hpp"

#include <iostream>
#include <thread>
#include <vector>

volatile bool flag[2] = { false, false };
volatile int turn{ 0 };

void workerFunction(int id) {
    do {

        if (id == 0) {
            flag[0] = true;
            turn = 0;

        } else {
            flag[1] = true;
            turn = 1;
        }

    } while (true);
}

int main() {

    std::thread t0(workerFunction, 0);
    std::thread t1(workerFunction, 1);

    if (t0.joinable()) {
        t0.join();
    }
    if (t1.joinable()) {
        t1.join();
    }

    return 0;
}
