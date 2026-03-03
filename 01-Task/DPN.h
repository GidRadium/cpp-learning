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

    // gcd(1, 0) = 1, gcd(1, a) = 1, gcd(0, 0) = UINT64_MAX, gcd(0, a) = a
    friend DPN gcd(const DPN& a, const DPN& b);
    // lcm(0, a) = 0, lcm(1, a) = a, lcm(0, 1) = 0
    friend DPN lcm(const DPN& a, const DPN& b);

    DPN& operator=(const DPN& other);
    DPN operator+(const DPN& other) const;
    friend std::ostream& operator<<(std::ostream& os, const DPN& dpn);

private:
    DPN(uint64_t value, uint64_t* prime_divisors, size_t prime_divisors_size, bool is_sorted);

    friend DPN LcmWithCorrectDPNs(const DPN& a, const DPN& b);
    friend DPN GcdWithCorrectDPNs(const DPN& a, const DPN& b);

    uint64_t value_;
    uint64_t* prime_divisors_;
    size_t prime_divisors_size_;
    bool is_correct_;
};
