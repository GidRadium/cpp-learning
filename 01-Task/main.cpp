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

    std::cout << "gcd(0, 0) = " << gcd(DPN(0), DPN(0)) << std::endl;
    std::cout << "gcd(0, 1) = " << gcd(DPN(0), DPN(1)) << std::endl;
    std::cout << "gcd(1, 1) = " << gcd(DPN(1), DPN(1)) << std::endl;
    std::cout << "gcd(0, a) = " << gcd(DPN(0), a) << std::endl;
    std::cout << "gcd(1, a) = " << gcd(DPN(1), a) << std::endl;

    std::cout << "lcm(0, 0) = " << lcm(DPN(0), DPN(0)) << std::endl;
    std::cout << "lcm(0, 1) = " << lcm(DPN(0), DPN(1)) << std::endl;
    std::cout << "lcm(1, 1) = " << lcm(DPN(1), DPN(1)) << std::endl;
    std::cout << "lcm(0, a) = " << lcm(DPN(0), a) << std::endl;
    std::cout << "lcm(1, a) = " << lcm(DPN(1), a) << std::endl;

    DPN c(12345);
    std::cout << "c = " << c << std::endl;
    c.ChangeDivisor(5, 7);
    std::cout << "c = " << c << std::endl;
    c.ChangeDivisor(5, 7);
    std::cout << "c = " << c << std::endl;
    c.ChangeDivisor(7, 2);
    std::cout << "c = " << c << std::endl;
    c.ChangeDivisor(2, 2002);
    std::cout << "c = " << c << std::endl;
    std::cout << "gcd(" << c << ", " << a << ") = " << gcd(c, a) << std::endl;
    std::cout << "lcm(" << c << ", " << a << ") = " << lcm(c, a) << std::endl;
    std::cout << "c = " << c << std::endl;
    c.Reinitialize();
    std::cout << "c = " << c << std::endl;
    std::cout << "gcd(" << c << ", " << a << ") = " << gcd(c, a) << std::endl;
    std::cout << "lcm(" << c << ", " << a << ") = " << lcm(c, a) << std::endl;
}
