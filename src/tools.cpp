#include "tanja84dk/tools.h"

#include <algorithm>
#include <ctime>
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

int Tanja84dk::get_date_stamp() noexcept {
    time_t timestamp;
    char output[10];
    struct tm* datetime;
    time(&timestamp);
    datetime = localtime(&timestamp);
    strftime(output, 10, "%Y%m%d", datetime);
    std::string data = output;
    return std::stoi(data);
}
