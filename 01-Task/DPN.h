#pragma once

#include <ostream>

// Divided Positive Number
class DPN {
private:
    unsigned int value;
    unsigned int* divisors;
    unsigned int divisors_size;
    bool is_sorted;

public:
    DPN(unsigned int value);
    DPN(const DPN& other);
    ~DPN();

    DPN& operator=(const DPN& other);
    DPN operator+(const DPN& other) const;
    friend std::ostream& operator<<(std::ostream& os, const DPN& dpn);

    void reinitialize();
    void change_divisor(unsigned int x, unsigned int y);

    unsigned int gcd(const DPN& other);
    unsigned int lcm(const DPN& other);
};
