#include "vector.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> stdVec(10);
    bd::vector<int> bdVec(10);

    std::cout << std::boolalpha << "Standard vector is empty: " << stdVec.empty()
              << " Brennan implementation is empty: " << bdVec.empty() << '\n';

    return 0;
}
