#include "tanja84dk/tools.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

bool Tanja84dk::file_exist(const std::string& filename) noexcept { return std::filesystem::exists(filename); }

void Tanja84dk::save_file(const std::string& filename, const std::vector<std::string>& vector_data) noexcept {
    std::ofstream fh(filename);
    std::ostream_iterator<std::string> output_iterator(fh, "\n");
    std::copy(std::begin(vector_data), std::end(vector_data), output_iterator);
    fh.close();
}
