#pragma once
#include <iostream>
#include <vector>



using uint32 = unsigned int;

class BigInt {

    std::vector<char> digits;

public:

    BigInt();

    BigInt(const char * str);

    BigInt(const BigInt& other) = default;

    BigInt& operator=(const BigInt& other) = default;

    ~BigInt() = default;

    BigInt operator+(const BigInt& other);

    BigInt& operator+=(const BigInt& other);

    BigInt operator*(const BigInt& other);

    BigInt& operator*=(const BigInt& other);

    bool operator>(const BigInt& other);

    bool operator<(const BigInt& other);

    bool operator==(const BigInt& other);

    bool operator!=(const BigInt& other);

    friend std::ostream& operator<<(std::ostream& out, const BigInt& data);

    friend std::istream& operator>>(std::istream& in, BigInt& data);

};