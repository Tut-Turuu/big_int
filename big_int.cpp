#include "big_int.hpp"
#include <cstring>
#include <string>
#include <algorithm>




BigInt::BigInt() {
    digits.resize(1);
    digits[0] = 0;
}

BigInt::BigInt(const char * str) {

    for (int i = strlen(str) - 1; i != -1; --i) {
        digits.push_back(str[i] - '0');
    }
}

BigInt BigInt::operator+(const BigInt& other) {
    BigInt result;

    size_t max_sz = digits.size() > other.digits.size() ? digits.size() : other.digits.size();
    auto& max_digits = digits.size() > other.digits.size() ? digits : other.digits;

    size_t min_sz = digits.size() > other.digits.size() ? other.digits.size() : digits.size();
    auto& min_digits = digits.size() > other.digits.size() ? other.digits : digits;


    result.digits.reserve(max_sz + 1);
    result.digits.resize(0);

    char carry = 0;

    for (size_t i = 0; i < min_sz; ++i) {
        char current = (digits[i] + other.digits[i] + carry) % 10;
        char next = (digits[i] + other.digits[i] + carry) / 10;

        result.digits.push_back(current);
        
        carry = next;
    }

    for (size_t i = min_sz; i < max_sz; ++i) {
        char current = (max_digits[i] + carry) % 10;
        char next = (max_digits[i] + carry) / 10;

        result.digits.push_back(current);
        
        carry = next;
    }

    if (carry) result.digits.push_back(carry);

    return result;
}

BigInt& BigInt::operator+=(const BigInt& other) {

    size_t max_sz = digits.size() > other.digits.size() ? digits.size() : other.digits.size();
    auto& max_digits = digits.size() > other.digits.size() ? digits : other.digits;

    size_t min_sz = digits.size() > other.digits.size() ? other.digits.size() : digits.size();
    auto& min_digits = digits.size() > other.digits.size() ? other.digits : digits;


    digits.reserve(max_sz + 1);
    digits.resize(max_sz);

    char carry = 0;

    for (size_t i = 0; i < min_sz; ++i) {
        
        digits[i] += other.digits[i] + carry;
        carry = digits[i] / 10;
        digits[i] %= 10;
    }

    for (size_t i = min_sz; i < max_sz; ++i) {
        if (&digits == &max_digits) {
            if (carry = 0) break;
            digits[i] += carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        } else {
            digits[i] = other.digits[i] + carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
    }

    if (carry) digits.push_back(carry);

    return *this;
    
}

BigInt BigInt::operator*(const BigInt& other) {
    BigInt result;

    size_t max_sz = digits.size() > other.digits.size() ? digits.size() : other.digits.size();
    auto& max_digits = digits.size() > other.digits.size() ? digits : other.digits;

    size_t min_sz = digits.size() > other.digits.size() ? other.digits.size() : digits.size();
    auto& min_digits = digits.size() > other.digits.size() ? other.digits : digits;


    result.digits.reserve(max_sz * min_sz);

    char carry = 0;

    for (size_t i = 0; i < digits.size(); ++i) {
        BigInt i_mult;
        i_mult.digits.resize(other.digits.size() * digits.size());
        for (size_t j = 0; j < other.digits.size(); ++j) {
            i_mult.digits[i+j] = (digits[i] * other.digits[j] + carry);
            carry = i_mult.digits[j+i] / 10;
            i_mult.digits[j+i] %= 10;
        }
        result += i_mult;
    }
    size_t i = result.digits.size() - 1;
    while (result.digits[i] == 0) {
        result.digits.pop_back();
        --i;
    }

    return result;
    
}

BigInt& BigInt::operator*=(const BigInt& other) {

}

bool BigInt::operator>(const BigInt& other) {
    if (digits.size() > other.digits.size()) return true;
    if (digits.size() < other.digits.size()) return false;

    for (int i = digits.size() - 1; i != -1; --i) {
        if (digits[i] > other.digits[i]) return true;
        if (digits[i] < other.digits[i]) return false;
    }
    return false;
}

bool BigInt::operator<(const BigInt& other) {
    if (digits.size() < other.digits.size()) return true;
    if (digits.size() > other.digits.size()) return false;

    for (int i = digits.size() - 1; i != -1; --i) {
        if (digits[i] < other.digits[i]) return true;
        if (digits[i] > other.digits[i]) return false;
    }
    return false;
}

bool BigInt::operator==(const BigInt& other) {
    if (digits.size() != other.digits.size()) return false;

    for (int i = digits.size() - 1; i != -1; --i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;;
}

bool BigInt::operator!=(const BigInt& other) {
    return !(*this == other); 
}

std::ostream& operator<<(std::ostream& out, const BigInt& data) {
    
    for (int i = data.digits.size() - 1; i != -1; --i) {
        out << char(data.digits[i] + '0');
    }
}

std::istream& operator>>(std::istream& in, BigInt& data) {
    std::string str;
    in >> str;
    data = BigInt(str.c_str());
}