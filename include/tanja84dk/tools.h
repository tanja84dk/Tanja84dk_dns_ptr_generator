#ifndef TANJA84DK_DNSGEN_TOOLS_H
#define TANJA84DK_DNSGEN_TOOLS_H

#include <string>
#include <vector>

namespace Tanja84dk {
bool file_exist(const std::string& filename) noexcept;

void save_file(const std::string& filename, const std::vector<std::string>& vector_data) noexcept;

int get_date_stamp() noexcept;

}  // namespace Tanja84dk

#endif  // TANJA84DK_DNSGEN_TOOLS_H
