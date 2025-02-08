#ifndef TANJA84DK_DNSGEN_DNS_THING_H
#define TANJA84DK_DNSGEN_DNS_THING_H

#include <tanja84dk/classes.h>

#include <string>

namespace Tanja84dk {

std::string gen_ip_network_name(const std::string& ip_as_0_range) noexcept;

std::string gen_rev(uint8_t& digit, Tanja84dk::IP_Address& IP_Obj, const std::string& domain) noexcept;

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
