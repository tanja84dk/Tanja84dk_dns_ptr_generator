#ifndef TANJA84DK_DNSGEN_TOOLS_H
#define TANJA84DK_DNSGEN_TOOLS_H
#include <tanja84dk/classes.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace Tanja84dk {
bool file_exist(const std::string& filename) noexcept;

void save_file(const std::string& filename, const std::vector<std::string>& vector_data) noexcept {
    std::ofstream fh(filename);
    std::ostream_iterator<std::string> output_iterator(fh, "\n");
    std::copy(std::begin(vector_data), std::end(vector_data), output_iterator);
    fh.close();
}

int get_date_stamp() noexcept {
    time_t timestamp;
    char output[10];
    struct tm* datetime;
    time(&timestamp);
    datetime = localtime(&timestamp);
    strftime(output, 10, "%Y%m%d", datetime);
    std::string data = output;
    return std::stoi(data);
}

}  // namespace Tanja84dk

#endif  // TANJA84DK_DNSGEN_TOOLS_H
