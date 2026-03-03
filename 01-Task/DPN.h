#pragma once

#include <cstdint>
#include <ostream>

// Divided Positive Number
class DPN {
private:
    uint64_t value;
    uint64_t* prime_divisors;
    size_t prime_divisors_size;
    bool is_sorted;

    DPN(uint64_t value, uint64_t* prime_divisors, size_t prime_divisors_size, bool is_sorted);
    friend DPN lcm_with_sorted(const DPN& a, const DPN& b);
    friend DPN gcd_with_sorted(const DPN& a, const DPN& b);

public:
    DPN(uint64_t value);
    DPN(const DPN& other);
    ~DPN();

    DPN& operator=(const DPN& other);
    DPN operator+(const DPN& other) const;
    friend std::ostream& operator<<(std::ostream& os, const DPN& dpn);

    void reinitialize();
    void change_divisor(uint64_t x, uint64_t y);

    friend DPN gcd(const DPN& a, const DPN& b);
    friend DPN lcm(const DPN& a, const DPN& b);
};
