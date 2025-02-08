#include <tanja84dk/dns_thing.h>

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
