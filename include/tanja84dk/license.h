#ifndef TANJA84DK_LICENSE_H
#define TANJA84DK_LICENSE_H

#include <string>

namespace Tanja84dk {
namespace license {

void print_title_for_licenses(const std::string &title) noexcept;
void print_all_licenses() noexcept;

const std::string get_project_license() noexcept;
const std::string get_argparse_license() noexcept;
const std::string get_fmtlib_license() noexcept;

}  // namespace license
}  // namespace Tanja84dk

#endif  // TANJA84DK_LICENSE_H
