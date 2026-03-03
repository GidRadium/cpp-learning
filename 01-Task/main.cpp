#include "DPN.h"

#include <iostream>

int main() {
    DPN a(12);
    DPN b(20);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "gcd(" << a << ", " << b << ") = " << gcd(a, b) << std::endl;
    std::cout << "lcm(" << a << ", " << b << ") = " << lcm(a, b) << std::endl;
}
