#pragma once

#include <cstdint>
#include <ostream>

// Divided Positive Number
class DPN {
public:
    DPN(uint64_t value);
    DPN(const DPN& other);
    ~DPN();

    void Reinitialize();
    void ChangeDivisor(uint64_t x, uint64_t y);

    friend DPN gcd(const DPN& a, const DPN& b);
    friend DPN lcm(const DPN& a, const DPN& b);

    DPN& operator=(const DPN& other);
    DPN operator+(const DPN& other) const;
    friend std::ostream& operator<<(std::ostream& os, const DPN& dpn);

private:
    DPN(uint64_t value, uint64_t* prime_divisors, size_t prime_divisors_size, bool is_sorted);

    friend DPN LcmWithSortedDPNs(const DPN& a, const DPN& b);
    friend DPN GcdWithSortedDPNs(const DPN& a, const DPN& b);

    uint64_t value_;
    uint64_t* prime_divisors_;
    size_t prime_divisors_size_;
    bool is_sorted_;
};
