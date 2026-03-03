#include "DPN.h"
#include <cstddef>

const size_t DPN_BUFFER_SIZE = 100;

uint64_t* get_new_sorted_divisiors_array(uint64_t value, size_t &new_size){
    new_size = 0;

    uint64_t *temp = new uint64_t[DPN_BUFFER_SIZE];
    for (size_t i = 1; i * i <= value; ++i) {
        while (value % i == 0) {
            temp[new_size] = i;
            ++new_size;
            value /= i;
        }
    }

    if (value != 1)
        temp[new_size++] = value;

    uint64_t* divisors = new uint64_t[new_size];
    for (size_t i = 0; i < new_size; ++i){
        divisors[i] = temp[i];
    }

    delete[] temp;

    return divisors;
}

bool is_prime(uint64_t value) {
    for (uint64_t i = 1; i * i <= value; i++){
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

DPN::DPN(uint64_t value,
         uint64_t* prime_divisors,
         size_t prime_divisors_size,
         bool is_sorted)
    : value(value),
      prime_divisors(prime_divisors),
      prime_divisors_size(prime_divisors_size),
      is_sorted(is_sorted) {
}

DPN::DPN(uint64_t value) : value(value) {
    prime_divisors = get_new_sorted_divisiors_array(value, prime_divisors_size);
    is_sorted = true;
}

DPN::DPN(const DPN& other) : value(other.value) {
    prime_divisors_size = other.prime_divisors_size;
    is_sorted = other.is_sorted;
    prime_divisors = new uint64_t[other.prime_divisors_size];
    for (size_t i = 0; i < other.prime_divisors_size; ++i)
        prime_divisors[i] = other.prime_divisors[i];
}

DPN::~DPN() {
    delete[] prime_divisors;
}

DPN& DPN::operator=(const DPN& other) {
    if (this == &other)
        return *this;

    value = other.value;
    delete[] prime_divisors;
    prime_divisors = new uint64_t[other.prime_divisors_size];
    for (size_t i = 0; i < other.prime_divisors_size; ++i)
        prime_divisors[i] = other.prime_divisors[i];

    prime_divisors_size = other.prime_divisors_size;
    is_sorted = other.is_sorted;

    return *this;
}

DPN DPN::operator+(const DPN& other) const {
    return DPN(value + other.value);
}

std::ostream& operator<<(std::ostream& os, const DPN& dpn) {
    os << dpn.value << ":[";
    for (size_t i = 0; i < dpn.prime_divisors_size; ++i) {
        if (i > 0) {
            os << ", ";
        }

        os << dpn.prime_divisors[i];
    }

    os << "]";

    return os;
}

void DPN::reinitialize() {
    delete[] prime_divisors;

    prime_divisors = get_new_sorted_divisiors_array(value, prime_divisors_size);
    is_sorted = true;
}

void DPN::change_divisor(uint64_t x, uint64_t y) {
    int x_index = -1;
    for (size_t i = 0; i < prime_divisors_size; i++){
        if (prime_divisors[i] == x) {
            x_index = i;
        }
    }

    if (x_index == -1){
        return;
    }

    if (!is_prime(y) ||
        (x_index > 0 && prime_divisors[x_index - 1] > x) ||
        (x_index + 1 < prime_divisors_size &&
         prime_divisors[x_index - 1] < x)) {
      is_sorted = false;
    }

    value = (value / x) * y;
    prime_divisors[x_index] = y;
}

DPN lcm_with_sorted(const DPN& a, const DPN& b) {
    size_t i = 0;
    size_t j = 0;
    uint64_t result = 1;
    uint64_t *temp = new uint64_t[DPN_BUFFER_SIZE];
    size_t buffer_size_used = 0;

    while (i < a.prime_divisors_size && j < b.prime_divisors_size) {
        if (a.prime_divisors[i] < b.prime_divisors[j]) {
            result *= a.prime_divisors[i];
            temp[buffer_size_used] = a.prime_divisors[i];
            ++buffer_size_used;
            ++i;
        } else if (a.prime_divisors[i] > b.prime_divisors[j]) {
            result *= b.prime_divisors[j];
            temp[buffer_size_used] = b.prime_divisors[j];
            ++buffer_size_used;
            ++j;
        } else {
            result *= a.prime_divisors[i];
            temp[buffer_size_used] = a.prime_divisors[i];
            ++buffer_size_used;
            ++i;
            ++j;
        }
    }

    while (i < a.prime_divisors_size) {
        result *= a.prime_divisors[i];
        temp[buffer_size_used] = a.prime_divisors[i];
        ++buffer_size_used;
        ++i;
    }

    while (j < b.prime_divisors_size) {
        result *= b.prime_divisors[j];
        temp[buffer_size_used] = b.prime_divisors[j];
        ++buffer_size_used;
        ++j;
    }

    uint64_t* divisors = new uint64_t[buffer_size_used];
    for (size_t i = 0; i < buffer_size_used; ++i){
        divisors[i] = temp[i];
    }

    delete[] temp;

    return DPN(result, divisors, buffer_size_used, true);
}

DPN gcd_with_sorted(const DPN& a, const DPN& b) {
    size_t i = 0;
    size_t j = 0;
    uint64_t result = 1;
    uint64_t *temp = new uint64_t[DPN_BUFFER_SIZE];
    size_t buffer_size_used = 0;

    while (i < a.prime_divisors_size && j < b.prime_divisors_size) {
        if (a.prime_divisors[i] < b.prime_divisors[j]) {
            ++i;
        } else if (a.prime_divisors[i] > b.prime_divisors[j]) {
            ++j;
        } else {
            result *= a.prime_divisors[i];
            temp[buffer_size_used] = a.prime_divisors[i];
            ++buffer_size_used;
            ++i;
            ++j;
        }
    }

    uint64_t* divisors = new uint64_t[buffer_size_used];
    for (size_t i = 0; i < buffer_size_used; ++i){
        divisors[i] = temp[i];
    }

    delete[] temp;

    return DPN(result, divisors, buffer_size_used, true);
}

DPN gcd(const DPN& a, const DPN& b) {
    if (a.is_sorted && b.is_sorted) {
        return gcd_with_sorted(a, b);
    } else if (a.is_sorted) {
        DPN b_new(b);
        b_new.reinitialize();
        return gcd_with_sorted(a, b_new);
    } else if (b.is_sorted) {
        DPN a_new(a);
        a_new.reinitialize();
        return gcd_with_sorted(a_new, b);
    } else {
        DPN a_new(a);
        DPN b_new(b);
        a_new.reinitialize();
        b_new.reinitialize();
        return gcd_with_sorted(a_new, b_new);
    }
}

DPN lcm(const DPN& a, const DPN& b) {
    if (a.is_sorted && b.is_sorted) {
        return lcm_with_sorted(a, b);
    } else if (a.is_sorted) {
        DPN b_new(b);
        b_new.reinitialize();
        return lcm_with_sorted(a, b_new);
    } else if (b.is_sorted) {
        DPN a_new(a);
        a_new.reinitialize();
        return lcm_with_sorted(a_new, b);
    } else {
        DPN a_new(a);
        DPN b_new(b);
        a_new.reinitialize();
        b_new.reinitialize();
        return lcm_with_sorted(a_new, b_new);
    }
}
