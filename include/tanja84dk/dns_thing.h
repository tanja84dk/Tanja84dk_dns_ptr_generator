#ifndef TANJA84DK_DNSGEN_DNS_THING_H
#define TANJA84DK_DNSGEN_DNS_THING_H

#include <tanja84dk/classes.h>

#include <map>
#include <string>

namespace Tanja84dk {

std::string gen_ip_network_name(const std::string& ip_as_0_range) noexcept;

std::string gen_rev(uint8_t& digit, Tanja84dk::IP_Address& IP_Obj, const std::string& domain) noexcept;

std::map<int, std::string> read_input_file(const std::string& filename) noexcept;

std::string right_align_header(std::string& data);

}  // namespace Tanja84dk

#endif  // TANJA84DK_DNSGEN_DNS_THING_H
