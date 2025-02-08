#include "tanja84dk/tools.h"

#include <filesystem>

bool Tanja84dk::file_exist(const std::string& filename) noexcept { return std::filesystem::exists(filename); }
