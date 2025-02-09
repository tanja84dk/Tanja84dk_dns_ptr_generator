#include "tanja84dk/calc_ip.h"

#include <bitset>
#include <iostream>
#include <string>

std::string Tanja84dk::Calc_IP::int_to_8bit_str(const int int_value) noexcept {
    std::bitset<8> binary = Tanja84dk::Calc_IP::int_to_8bit(int_value);
    std::string output_str = binary.to_string<char, std::char_traits<char>, std::allocator<char> >();
    return output_str;
}

std::bitset<8> Tanja84dk::Calc_IP::int_to_8bit(const int int_value) noexcept { return std::bitset<8>(int_value); }
