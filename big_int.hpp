#pragma once
#include <iostream>
#include <vector>


using uint32 = unsigned int;

class BigInt {

    class DigitVector {
        std::vector<char> char_vec;
        uint32 sz;

        class reference {
            char* byte_ptr;
            bool is_left; // left 4 bits or right 4 bits of char

        public:

            reference(char* byte_ptr, bool is_left);

            reference& operator=(char digit);

            operator char() const;
        };

    public:

        void push_back(char digit);

        void pop_back();

        reference operator[](uint32 index);

        const reference operator[](uint32 index) const;


    };

    DigitVector digits;

public:

    BigInt();

    BigInt(const char* str);

    BigInt(const BigInt& other);

    BigInt& operator=(const BigInt& other);

    ~BigInt();

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