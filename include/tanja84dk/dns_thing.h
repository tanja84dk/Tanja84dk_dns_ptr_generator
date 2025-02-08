#ifndef TANJA84DK_DNSGEN_DNS_THING_H
#define TANJA84DK_DNSGEN_DNS_THING_H

#include <tanja84dk/classes.h>

#include <fstream>
#include <iostream>
#include <string>

namespace Tanja84dk {

std::string gen_ip_network_name(const std::string& ip_as_0_range) noexcept {
    std::string buffer = "";
    std::string return_data = "";
    int sep_counter = 0;
    bool break_out = false;
    for (int i = 0; i < ip_as_0_range.length(); i++) {
        if (sep_counter == 3) {
            break;
        } else {
            buffer = ip_as_0_range[i];
        }
        if (buffer == ".") {
            sep_counter += 1;
            return_data.append("-");
        } else {
            return_data.append(buffer);
        }
    }
    return return_data;
}

std::string gen_rev(uint8_t& digit, Tanja84dk::IP_Address& IP_Obj, const std::string& domain) noexcept {
    int digit_length = std::to_string(digit).length();
    int padding = 8 - digit_length;
    std::string ip_network_str =
        fmt::format("{0}-{1}-{2}", IP_Obj.get_first(), IP_Obj.get_second(), IP_Obj.get_third());

    if (IP_Obj.host_list.count(digit)) {
        if (IP_Obj.host_list.find(digit)->second.back() != '.') {
            return fmt::format("{0}{1}IN      PTR     {2}.{3}.", digit, std::string(padding, ' '),
                               IP_Obj.host_list.find(digit)->second, domain);

        } else {
            return fmt::format("{0}{1}IN      PTR     {2}", digit, std::string(padding, ' '),
                               IP_Obj.host_list.find(digit)->second);
        }
    }
    return fmt::format("{0}{1}IN      PTR     {2}-{0}.dyn.{3}.", digit, std::string(padding, ' '), ip_network_str,
                       domain);
}

std::map<int, std::string> read_input_file(const std::string& filename) noexcept {
    std::map<int, std::string> output;

    int key = {};
    std::string value = {};

    std::ifstream fh(filename);

    while (fh >> key >> value) {
        output[key] = value;
    }
    fh.close();
    return output;
}

std::string right_align_header(std::string& data) {
    int data_length = data.length();
    int start_point = 33 - data_length;
    return fmt::format("{}{}", std::string(start_point, ' '), data);
}

}  // namespace Tanja84dk

#endif  // TANJA84DK_DNSGEN_DNS_THING_H
