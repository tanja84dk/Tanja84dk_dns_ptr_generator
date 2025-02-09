#ifndef TANJA84DK_DNSGEN_CALC_IP_H
#define TANJA84DK_DNSGEN_CALC_IP_H

#include <bitset>
#include <string>

namespace Tanja84dk {
namespace Calc_IP {
void get_ip(const std::string& ipaddress_str) noexcept;
std::bitset<8> int_to_8bit(const int int_value) noexcept;
std::string int_to_8bit_str(const int int_value) noexcept;
}  // namespace Calc_IP
}  // namespace Tanja84dk

#endif  // TANJA84DK_DNSGEN_CALC_IP_H
