#include "big_int.hpp"

// REFERENCE

BigInt::DigitVector::reference::reference(char* byte_ptr, bool is_left): byte_ptr(byte_ptr), is_left(is_left) {}

BigInt::DigitVector::reference& BigInt::DigitVector::reference::operator=(char digit) {
    if (is_left) *byte_ptr = (*byte_ptr & 0b00001111) + (digit << 4);
    else *byte_ptr = (*byte_ptr & 0b11110000) + digit;
}

BigInt::DigitVector::reference::operator char() const {
    return is_left ? (*byte_ptr >> 4) & 0b00001111 : (*byte_ptr & 0b00001111);
}

// DIGIT_VECTOR

void BigInt::DigitVector::push_back(char digit) {
    if (sz == char_vec.size() * 2) {
        push_back(digit << 4);
        return;
    }
    if (sz % 2) char_vec[sz / 2] = char_vec[sz / 2] & 0b11110000 + digit;
    else char_vec[sz / 2] = (char_vec[sz / 2] & 0b00001111) + (digit << 4);

    ++sz;
}

void BigInt::DigitVector::pop_back() {
    --sz;
}

BigInt::DigitVector::reference BigInt::DigitVector::operator[](uint32 index) {

}

const BigInt::DigitVector::reference BigInt::DigitVector::operator[](uint32 index) const {

}