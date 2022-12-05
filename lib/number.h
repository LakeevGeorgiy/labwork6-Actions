#pragma once
#include <cinttypes>
#include <iostream>
#include <vector>

struct uint2022_t {
    uint32_t first_zero_index= 67;
    static const size_t size_number = 68, max_value = 1'000'000'000;
    uint32_t number[size_number];
    uint2022_t() {
        for (int i = 0; i < size_number; i++)
            number[i] = 0;
    }
    uint2022_t(const uint2022_t &value){
        for (int i = 0; i < size_number; i++)
            number[i] = value.number[i];
        first_zero_index = value.first_zero_index;
    }
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator+(const uint2022_t& lhs, const int& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
