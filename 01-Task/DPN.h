#pragma once

#include <cstdint>
#include <ostream>

// Divided Positive Number.
// Represents uint64_t with it prime factorization representation.
// Allocates memmory for factorization array.
// Not thread-safe.
class DPN {
public:
    // Inits from value and calculates it сanonical prime factorization.
    // Uses temp memmory to calculate.
    // Edge cases: if value < 2 - do not allocates memmory.
    DPN(uint64_t value);

    // Inits by getting deep copy.
    // Edge cases: if value < 2 - do not allocates memmory.
    DPN(const DPN& other);

    // Frees all allocated memmory.
    // Edge cases: if value < 2 - no allocated memmory to free.
    ~DPN();

    // Recalculates same value as сanonical prime factorization.
    // Allocates temp memmory using "new"
    void Reinitialize();

    // Replaces the first occurrence of x with y.
    // Edge cases: do nothing when value < 2 or y = 0;
    void ChangeDivisor(uint64_t x, uint64_t y);

    // Returns the greatest common divisor of two DPN
    // Edge cases: gcd(0, 1) = 1, gcd(1, a) = 1, gcd(0, 0) = UINT64_MAX, gcd(0, a) = a.
    friend DPN gcd(const DPN& a, const DPN& b);

    // Returns the least common multiple
    // Edge cases: lcm(0, a) = 0, lcm(1, a) = a, lcm(0, 1) = 0.
    friend DPN lcm(const DPN& a, const DPN& b);

    // Deep copy.
    // Allocates same memmory as other's.
    DPN& operator=(const DPN& other);

    // Returns DPN inited by summ of the values
    DPN operator+(const DPN& other) const;

    // Pull object to stream in value:[p1, p2, p3, ...] form.
    // For example: 0:[], 1:[], 3:[3], 10:[2, 5].
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
