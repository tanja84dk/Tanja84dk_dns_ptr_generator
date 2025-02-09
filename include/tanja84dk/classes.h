#ifndef TANJA84DK_DNSGEN_CLASSES_H
#define TANJA84DK_DNSGEN_CLASSES_H
#include <fmt/core.h>
#include <tanja84dk/calc_ip.h>

#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace Tanja84dk {
class IP_Address {
   private:
    std::string _full_ip_address = {};
    std::string _first = {};
    std::string _second = {};
    std::string _third = {};
    std::string _fourth = {};

    std::array<std::bitset<8>, 4> _binary_array;

    void _clear_impl() noexcept {
        this->_first.clear();
        this->_second.clear();
        this->_third.clear();
        this->_fourth.clear();
        this->_full_ip_address.clear();
    }

    void _set_ip_impl(const std::string& ipaddress_string) noexcept {
        this->_clear_impl();
        this->_full_ip_address = ipaddress_string;
        int sep_counter = 0;
        std::string buffer = {};
        for (int i = 0; i < this->_full_ip_address.length(); i++) {
            buffer = this->_full_ip_address[i];
            if (buffer == ".") {
                sep_counter += 1;
                continue;
            }
            if (sep_counter == 0) {
                this->_first.append(buffer);
            } else if (sep_counter == 1) {
                this->_second.append(buffer);
            } else if (sep_counter == 2) {
                this->_third.append(buffer);
            } else {
                this->_fourth.append(buffer);
            }
        }

        this->_binary_array[0] = Tanja84dk::Calc_IP::int_to_8bit(std::stoi(this->_first));
        this->_binary_array[1] = Tanja84dk::Calc_IP::int_to_8bit(std::stoi(this->_second));
        this->_binary_array[2] = Tanja84dk::Calc_IP::int_to_8bit(std::stoi(this->_third));
        this->_binary_array[3] = Tanja84dk::Calc_IP::int_to_8bit(std::stoi(this->_fourth));
    }

   public:
    IP_Address(const std::string& ipaddress_string) noexcept { this->_set_ip_impl(ipaddress_string); };
    void set_new_ip(const std::string& ipaddress_string) noexcept { this->_set_ip_impl(ipaddress_string); };
    std::string get_first() noexcept { return this->_first; }
    const std::string get_second() noexcept { return this->_second; }
    const std::string get_third() noexcept { return this->_third; }
    const std::string get_fourth() noexcept { return this->_fourth; }

    std::map<int, std::string> host_list = {};

    const std::string get_full_test() noexcept {
        return fmt::format("{}.{}.{}.{}", this->get_first(), this->get_second(), this->get_third(), this->get_fourth());
    }

    void print_as_binary_str() noexcept {
        std::string output_str = "";

        for (int i = 0; i < this->_binary_array.size(); i++) {
            std::bitset<8> binary = this->_binary_array[i];
            output_str.append(binary.to_string<char, std::char_traits<char>, std::allocator<char> >());
            if (i != this->_binary_array.size()) {
                output_str.append(" ");
            }
        }
        fmt::print("{}\n", output_str);
    }

    void print_as_hex() noexcept {
        std::stringstream output_value = {};
        output_value << "0x";
        for (int i = 0; i < this->_binary_array.size(); i++) {
            output_value << std::hex << std::setfill('0') << std::setw(2) << this->_binary_array[i].to_ulong();

            // if (i < (this->_binary_array.size() - 1)) {
            //     output_value << ' ';
            // }
        }
        fmt::print("{0}\n", output_value.str());
    }
};

}  // namespace Tanja84dk

#endif  // TANJA84DK_DNSGEN_CLASSES_H
