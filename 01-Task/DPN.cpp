#include "DPN.h"

DPN::DPN(unsigned int value) : value(value) {
    this->divisors = new unsigned int[100];
    this->divisors_size = 0;
    for (unsigned int i = 1; i <= value; i++)
        if (value % i == 0)
            this->divisors[this->divisors_size++] = i;

    this->is_sorted = true;
}

DPN::DPN(const DPN& other) : value(other.value) {
    this->divisors = new unsigned int[other.divisors_size];
    for (unsigned int i = 0; i < other.divisors_size; i++)
        this->divisors[i] = other.divisors[i];

    this->divisors_size = other.divisors_size;
    this->is_sorted = other.is_sorted;
}

DPN::~DPN() {
    delete[] this->divisors;
}

DPN& DPN::operator=(const DPN& other) {
    if (this == &other)
        return *this;

    this->value = other.value;
    delete[] this->divisors;
    this->divisors = new unsigned int[other.divisors_size];
    for (unsigned int i = 0; i < other.divisors_size; i++)
        this->divisors[i] = other.divisors[i];

    this->divisors_size = other.divisors_size;
    this->is_sorted = other.is_sorted;

    return *this;
}

DPN DPN::operator+(const DPN& other) const {
    return DPN(this->value + other.value);
}
