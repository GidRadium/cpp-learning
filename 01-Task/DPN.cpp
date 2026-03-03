#include "DPN.h"
#include <cstddef>

constexpr size_t kDpnBufferSize = 100;

uint64_t* GetNewSortedDivisiorsArray(uint64_t value, size_t &new_size) {
    new_size = 0;

    if (value < 2) {
        return nullptr;
    }

    uint64_t *temp = new uint64_t[kDpnBufferSize];
    for (size_t i = 2; i * i <= value; ++i) {
        while (value % i == 0) {
            temp[new_size] = i;
            ++new_size;
            value /= i;
        }
    }

    if (value != 1) {
        temp[new_size++] = value;
    }

    uint64_t* divisors = new uint64_t[new_size];
    for (size_t i = 0; i < new_size; ++i){
        divisors[i] = temp[i];
    }

    delete[] temp;

    return divisors;
}

bool IsPrime(uint64_t value) {
    if (value < 2) {
        return false;
    }

    if (value == 2) {
        return true;
    }

    for (uint64_t i = 2; i * i <= value; ++i){
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

DPN::DPN(uint64_t value,
         uint64_t* prime_divisors,
         size_t prime_divisors_size,
         bool is_sorted):
    value_(value),
    prime_divisors_(prime_divisors),
    prime_divisors_size_(prime_divisors_size),
    is_correct_(is_sorted) {
}

DPN::DPN(uint64_t value) : value_(value) {
    prime_divisors_size_ = 0;
    prime_divisors_ = GetNewSortedDivisiorsArray(value, prime_divisors_size_);
    is_correct_ = true;
}

DPN::DPN(const DPN& other) : value_(other.value_) {
    prime_divisors_size_ = other.prime_divisors_size_;
    is_correct_ = other.is_correct_;

    if (prime_divisors_size_ > 0) {
        prime_divisors_ = new uint64_t[other.prime_divisors_size_];
        for (size_t i = 0; i < other.prime_divisors_size_; ++i) {
            prime_divisors_[i] = other.prime_divisors_[i];
        }
    } else {
        prime_divisors_ = nullptr;
    }
}

DPN::~DPN() {
    if (prime_divisors_ != nullptr) {
        delete[] prime_divisors_;
    }
}

DPN& DPN::operator=(const DPN& other) {
    if (this == &other)
        return *this;

    value_ = other.value_;
    if (prime_divisors_ != nullptr) {
        delete[] prime_divisors_;
        prime_divisors_ = nullptr;
    }

    if (other.prime_divisors_size_ > 0) {
        prime_divisors_ = new uint64_t[other.prime_divisors_size_];
        for (size_t i = 0; i < other.prime_divisors_size_; ++i) {
            prime_divisors_[i] = other.prime_divisors_[i];
        }
    }

    prime_divisors_size_ = other.prime_divisors_size_;
    is_correct_ = other.is_correct_;

    return *this;
}

DPN DPN::operator+(const DPN& other) const {
    return DPN(value_ + other.value_);
}

std::ostream& operator<<(std::ostream& os, const DPN& dpn) {
    os << dpn.value_ << ":[";
    for (size_t i = 0; i < dpn.prime_divisors_size_; ++i) {
        if (i > 0) {
            os << ", ";
        }

        os << dpn.prime_divisors_[i];
    }

    os << "]";

    return os;
}

void DPN::Reinitialize() {
    if (prime_divisors_ != nullptr) {
        delete[] prime_divisors_;
    }

    prime_divisors_ = GetNewSortedDivisiorsArray(value_, prime_divisors_size_);
    is_correct_ = true;
}

void DPN::ChangeDivisor(uint64_t x, uint64_t y) {
    if (prime_divisors_ == nullptr) {
        return;
    }

    int x_index = -1;
    for (size_t i = 0; i < prime_divisors_size_; i++){
        if (prime_divisors_[i] == x) {
            x_index = i;
        }
    }

    if (x_index == -1){
        return;
    }

    if (!IsPrime(y) ||
        (x_index > 0 && prime_divisors_[x_index - 1] > y) ||
        (x_index + 1 < prime_divisors_size_ &&
         prime_divisors_[x_index + 1] < y)) {
      is_correct_ = false;
    }

    value_ = (value_ / x) * y;
    prime_divisors_[x_index] = y;
}

// gcd(1, 0) = 1, gcd(1, a) = 1, gcd(0, 0) = UINT64_MAX, gcd(0, a) = a
DPN GcdWithCorrectDPNs(const DPN& a, const DPN& b) {
    if (a.value_ == 1 || b.value_ == 1) {
        return DPN(1);
    } else if (a.value_ == 0 && b.value_ == 0) {
        return DPN(UINT64_MAX);
    } else if (a.value_ == 0) {
        return DPN(b);
    } else if (b.value_ == 0) {
        return DPN(a);
    }

    size_t i = 0;
    size_t j = 0;
    uint64_t result = 1;
    uint64_t *temp = new uint64_t[kDpnBufferSize];
    size_t buffer_size_used = 0;

    while (i < a.prime_divisors_size_ && j < b.prime_divisors_size_) {
        if (a.prime_divisors_[i] < b.prime_divisors_[j]) {
            ++i;
        } else if (a.prime_divisors_[i] > b.prime_divisors_[j]) {
            ++j;
        } else {
            result *= a.prime_divisors_[i];
            temp[buffer_size_used] = a.prime_divisors_[i];
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

// lcm(0, a) = 0, lcm(1, a) = a, lcm(0, 1) = 0
DPN LcmWithCorrectDPNs(const DPN& a, const DPN& b) {

    if (a.value_ == 0 || b.value_ == 0) {
        return DPN(0);
    } else if (a.value_ == 1) {
        return DPN(b);
    } else if (b.value_ == 1) {
        return DPN(a);
    }

    size_t i = 0;
    size_t j = 0;
    uint64_t result = 1;
    uint64_t *temp = new uint64_t[kDpnBufferSize];
    size_t buffer_size_used = 0;

    while (i < a.prime_divisors_size_ && j < b.prime_divisors_size_) {
        if (a.prime_divisors_[i] < b.prime_divisors_[j]) {
            result *= a.prime_divisors_[i];
            temp[buffer_size_used] = a.prime_divisors_[i];
            ++buffer_size_used;
            ++i;
        } else if (a.prime_divisors_[i] > b.prime_divisors_[j]) {
            result *= b.prime_divisors_[j];
            temp[buffer_size_used] = b.prime_divisors_[j];
            ++buffer_size_used;
            ++j;
        } else {
            result *= a.prime_divisors_[i];
            temp[buffer_size_used] = a.prime_divisors_[i];
            ++buffer_size_used;
            ++i;
            ++j;
        }
    }

    while (i < a.prime_divisors_size_) {
        result *= a.prime_divisors_[i];
        temp[buffer_size_used] = a.prime_divisors_[i];
        ++buffer_size_used;
        ++i;
    }

    while (j < b.prime_divisors_size_) {
        result *= b.prime_divisors_[j];
        temp[buffer_size_used] = b.prime_divisors_[j];
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

DPN gcd(const DPN& a, const DPN& b) {
    if (a.is_correct_ && b.is_correct_) {
        return GcdWithCorrectDPNs(a, b);
    } else if (a.is_correct_) {
        DPN b_new(b);
        b_new.Reinitialize();
        return GcdWithCorrectDPNs(a, b_new);
    } else if (b.is_correct_) {
        DPN a_new(a);
        a_new.Reinitialize();
        return GcdWithCorrectDPNs(a_new, b);
    } else {
        DPN a_new(a);
        DPN b_new(b);
        a_new.Reinitialize();
        b_new.Reinitialize();
        return GcdWithCorrectDPNs(a_new, b_new);
    }
}

DPN lcm(const DPN& a, const DPN& b) {
    if (a.is_correct_ && b.is_correct_) {
        return LcmWithCorrectDPNs(a, b);
    } else if (a.is_correct_) {
        DPN b_new(b);
        b_new.Reinitialize();
        return LcmWithCorrectDPNs(a, b_new);
    } else if (b.is_correct_) {
        DPN a_new(a);
        a_new.Reinitialize();
        return LcmWithCorrectDPNs(a_new, b);
    } else {
        DPN a_new(a);
        DPN b_new(b);
        a_new.Reinitialize();
        b_new.Reinitialize();
        return LcmWithCorrectDPNs(a_new, b_new);
    }
}
