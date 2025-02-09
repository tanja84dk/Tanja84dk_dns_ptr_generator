#include <fmt/core.h>
#include <tanja84dk/calc_ip.h>
#include <tanja84dk/classes.h>
#include <tanja84dk/dns_thing.h>
#include <tanja84dk/license.h>
#include <tanja84dk/tools.h>

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::vector<std::string> header;
    std::string ip_network_dns_name;

    std::string file_name = {};
    std::string domain = {};
    std::string network_name = {};

    if (argv[1] == std::string("-h") or argv[1] == std::string("--help")) {
        fmt::print("This is the help\n");
        return EXIT_SUCCESS;
    }
    if (argv[1] == std::string("--license")) {
        Tanja84dk::license::print_all_licenses();
        return EXIT_SUCCESS;
    }

    if (argc > 1) {
        network_name = argv[1];
        file_name = network_name + ".list";
        domain = argv[2];
    } else {
        network_name = "192.168.1.0";
        file_name = network_name + ".list";
        domain = "example.com";
    }
    Tanja84dk::IP_Address Ip_Address_Obj(network_name);

    if (Tanja84dk::file_exist(file_name)) {
        Ip_Address_Obj.host_list = Tanja84dk::read_input_file(file_name);
    }

    std::string nameserver = fmt::format("ns.{0}", domain);
    std::string email_formatted = fmt::format("hostmaster.{0}", domain);

    std::size_t date_stamp = Tanja84dk::get_date_stamp();
    std::string serial = std::to_string(date_stamp);
    serial = serial + "01";
    std::string refresh = "604800";
    std::string retry = "86400";
    std::string expire = "2419200";
    std::string negative_cache_ttl = "604800";

    header.push_back(fmt::format("$TTL\t604800"));
    header.push_back(fmt::format("@\tIN\tSOA\t{0}.\t{1}. (", nameserver, email_formatted));
    header.push_back(Tanja84dk::right_align_header(serial) + "         ; Serial");
    header.push_back(Tanja84dk::right_align_header(refresh) + "         ; Refresh");
    header.push_back(Tanja84dk::right_align_header(retry) + "         ; Retry");
    header.push_back(Tanja84dk::right_align_header(expire) + "         ; Expire");
    header.push_back(Tanja84dk::right_align_header(negative_cache_ttl) + " )       ; Negative Cache TTL\n;");
    header.push_back(fmt::format("{0}       IN      NS      {1}.", "@", nameserver));
    for (u_int8_t i = 0; i < 255; i++) {
        header.push_back(gen_rev(i, Ip_Address_Obj, domain));
    }

    std::string rev_network =
        fmt::format("{0}.{1}.{2}", Ip_Address_Obj.get_third(), Ip_Address_Obj.get_second(), Ip_Address_Obj.get_first());

    std::string output_file_name = fmt::format("/buildtest/Cpp-Tanja84dk-DnsSync/pri.{0}.in-addr.arpa", rev_network);

    Tanja84dk::save_file(output_file_name, header);

    return 0;
}
