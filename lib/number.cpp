#include "number.h"
#include <algorithm>
#include <cmath>
#include <string>

uint2022_t from_uint(uint32_t i) {
    uint2022_t value;
    value.first_zero_index = value.size_number - 2;
    value.number[value.size_number- 1] = i;
    value.number[value.size_number - 2] = value.number[value.size_number - 1] / value.max_value;
    value.number[value.size_number - 1] %= value.max_value;
    if (value.number[value.size_number - 2] > 0)
        value.first_zero_index = value.size_number - 3;
    return value;
}

uint2022_t from_string(const char* buff) {
    const char* begin = buff, *end = buff;
    while (*end != '\0')
        end++;
    end--;

    uint2022_t value;
    uint32_t temp_value = 0, pok = 0, index = value.size_number - 1;

    while (begin <= end) {
        char char_digit = *end;
        int digit = (char_digit -'0');
        temp_value = temp_value + digit * pow(10, pok++);
        if (pok == 9 || end == begin) {
            value.number[index--] += temp_value;
            temp_value = 0;
            pok = 0;
        }
        end--;
    }
    value.first_zero_index = index;
    return value;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t value;
    for (int i = value.size_number - 1; i >= std::min(lhs.first_zero_index, rhs.first_zero_index); i--) {
        value.number[i] += lhs.number[i] + rhs.number[i];
        value.first_zero_index = i;
        if (value.number[i] <= value.max_value - 1)
            continue;
        if (i == 0)
            std::cerr << "Programm failed!";
        else {
            value.number[i - 1] += value.number[i] / value.max_value;
            value.number[i] %= value.max_value;
            value.first_zero_index = i - 1;
        }
    }
    return value;
}

uint2022_t operator+(const uint2022_t& lhs, const int& rhs){
    uint2022_t value = lhs;

    value.number[value.size_number - 1] += rhs;
    size_t i = value.size_number - 1;
    value.first_zero_index = i - 1;

    while (value.number[i] >= value.max_value){
        value.number[i - 1] += (value.number[i] % value.max_value);
        value.number[i] %= value.max_value;
        value.first_zero_index--;
    }
    return value;
}


uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t value;
    for (int i = value.size_number - 1; i >= std::min(lhs.first_zero_index, rhs.first_zero_index); i--) {
        value.first_zero_index = i;
        if (lhs.number[i] >= rhs.number[i]) {
            value.number[i] += lhs.number[i] - rhs.number[i];
        } else {
            value.number[i - 1]--;
            value.number[i] += value.max_value - rhs.number[i] + lhs.number[i];
        }
    }
    return value;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t value;
    for (size_t i = value.size_number; i > rhs.first_zero_index; i--) {
        for (size_t j = value.size_number; j > lhs.first_zero_index; j--) {

            unsigned long long mul = static_cast<unsigned long long>(rhs.number[i]) * lhs.number[j];
            uint32_t index_mul = 2 * value.size_number - (i + j);
            uint32_t add_sum = mul % value.max_value;
            value.number[value.size_number - index_mul] += add_sum;

            unsigned long long mod = ((mul - add_sum) + value.number[value.size_number - index_mul]) / value.max_value;
            value.number[value.size_number - index_mul] %= value.max_value;
            value.first_zero_index = std::min(value.first_zero_index, (uint32_t) value.size_number - index_mul - 1);

            if (mod == 0)
                continue;
            if (value.size_number - index_mul - 1 < 0) {
                std::cerr << "Programm Failed!\n";
            }

            value.number[value.size_number - index_mul - 1] += mod;
            value.first_zero_index = std::min(value.first_zero_index, (uint32_t) value.size_number - index_mul - 2);
        }
    }
    return value;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t value;
    uint2022_t copy_lhs = lhs;
    uint2022_t mul10 = from_uint(10);

    size_t size_number_copy_lhs = lhs.size_number - lhs.first_zero_index - 2;
    size_t size_number_copy_rhs = rhs.size_number - rhs.first_zero_index - 2;

    size_t cnt_digit_copy_lhs = std::max((size_t)0, size_number_copy_lhs) * 9 + ceil(log10(lhs.number[lhs.first_zero_index + 1]));
    size_t cnt_digit_copy_rhs = std::max((size_t)0, size_number_copy_rhs) * 9 + ceil(log10(rhs.number[rhs.first_zero_index + 1]));
    size_t cnt_digit_rhs = cnt_digit_copy_rhs;

    uint32_t temp = cnt_digit_copy_lhs - cnt_digit_rhs;
    while (rhs <= copy_lhs) {
        uint2022_t copy_rhs = rhs;
        std::string cnt_zero(temp, '0');
        cnt_zero = '1' + cnt_zero;

        const char *buf = cnt_zero.c_str();
        uint2022_t mul = from_string(buf);
        copy_rhs = copy_rhs * mul;

        uint32_t ans = 0;
        while (copy_rhs <= copy_lhs)  {
            copy_lhs = copy_lhs - copy_rhs;
            ans = ans + 1;
        }
        value = value * mul10;
        value = value + ans;
        temp--;
        value.first_zero_index = 0;
    }
    for (int i = 0; i < value.size_number; i++){
        if (value.number[i] != 0){
            value.first_zero_index = i -1;
            break;
        }
    }
    return value;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < lhs.size_number; i++){
        if (lhs.number[i] != rhs.number[i])
            return false;
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < lhs.size_number; i++){
        if (lhs.number[i] != rhs.number[i])
            return true;
    }
    return false;
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs){
    for (size_t i = 0; i < lhs.size_number; i++){
        if (lhs.number[i] < rhs.number[i])
            return true;
    }
    return false;
}

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < lhs.size_number; i++){
        if (lhs.number[i] < rhs.number[i])
            return true;
        if (lhs.number[i] > rhs.number[i])
            return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    for (int i = value.first_zero_index + 1; i < value.size_number; i++) {
        if (i == value.first_zero_index + 1) {
            stream << value.number[i];
            continue;
        }
        uint32_t size = ceil(log10(value.number[i]));
        while (size < 9){
            stream << 0;
            size++;
        }
        stream << value.number[i];
    }
    return stream;
}