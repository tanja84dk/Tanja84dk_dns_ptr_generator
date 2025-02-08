#include <fmt/core.h>
#include <tanja84dk/license.h>
#include <tanja84dk_licenses_macro.h>

#include <string>

#include "license_helper.h"

using namespace Tanja84dk;
/**
 * @brief Printing the title part of the license
 *
 * @param title
 */
void license::print_title_for_licenses(const std::string &title) noexcept {
    fmt::print(
        "---------------------------\n"
        "    {}\n"
        "---------------------------\n",
        title);
}

/**
 * @brief Print all licenses
 *
 */
void license::print_all_licenses() noexcept {
    Tanja84dk::license::print_title_for_licenses("Tanja84dk_dns_ptr_generator 0.1.0");
    fmt::print("{}\n\n", Tanja84dk::license::get_project_license());

    Tanja84dk::license::print_title_for_licenses("fmt/fmtlib 11.1.3");
    fmt::print("{}\n\n", Tanja84dk::license::get_fmtlib_license());
}

const std::string license::get_project_license() noexcept {
    std::string license = tanja84dk_dns_ptr_zone_generator_LICENSE;
    Tanja84dk::dns_gen_private::replace_all(license, ";", "\n");
    return license;
}

const std::string license::get_fmtlib_license() noexcept {
    std::string license = fmt_LICENSE;
    Tanja84dk::dns_gen_private::replace_all(license, ";", "\n");
    return license;
}
