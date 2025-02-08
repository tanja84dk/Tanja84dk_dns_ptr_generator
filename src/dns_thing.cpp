#include "tanja84dk/dns_thing.h"

#include <fmt/core.h>
#include <tanja84dk/classes.h>

#include <map>
#include <string>

std::string Tanja84dk::gen_ip_network_name(const std::string& ip_as_0_range) noexcept {
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

std::string Tanja84dk::gen_rev(uint8_t& digit, Tanja84dk::IP_Address& IP_Obj, const std::string& domain) noexcept {
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
