#include <fmt/core.h>
#include <tanja84dk/calc_ip.h>
#include <tanja84dk/classes.h>
#include <tanja84dk/dns_thing.h>
#include <tanja84dk/license.h>
#include <tanja84dk/tools.h>

#include <argparse/argparse.hpp>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Parsed_Args {
    std::string network = "";
    std::string domain = "";
    std::string list_filename = "";
    /* data */
};

int main(int argc, char** argv) {
    Parsed_Args Parsed_Arguments;
    argparse::ArgumentParser parser("Tanja84dk_dns_ptr_generator", "0.1.0");
    parser.add_argument("-l", "--license")
        .action([&](const auto& /*unused*/) {
            Tanja84dk::license::print_all_licenses();
            std::exit(0);
        })
        .help("Shows the licenses")
        .default_value(false)
        .implicit_value(true)
        .nargs(0);
    parser.add_argument("-n", "--network")
        .required()
        .store_into(Parsed_Arguments.network)
        .metavar("NETWORK_ADDRESS")
        .help("This is the network address as a /24 without the /24.\nSo as example --network 10.10.10.0");
    parser.add_argument("-d", "--domain")
        .required()
        .store_into(Parsed_Arguments.domain)
        .metavar("DOMAIN")
        .help("The domain/subdomain the rdns/ptr zone is for");
    parser.add_argument("-f", "--list-file")
        .store_into(Parsed_Arguments.list_filename)
        .metavar("FILENAME")
        .help(
            "Optional list file for ip and hostname.\n"
            "If hostname ends with a . then it's seen as a fqdn address and else its adding the domain.\n"
            "Default filename it looks for is network address with the extention .list\n"
            "So an example 10.10.10.0.list and if none are given then it's just generating ptr based on ip and domain");

    try {
        parser.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return EXIT_FAILURE;
    }

    if (Parsed_Arguments.network.size() <= 0) {
        fmt::print("Networking is not set\n");
        std::cerr << parser;
        return EXIT_FAILURE;
    }

    if (Parsed_Arguments.domain.size() <= 0) {
        fmt::print("Domain is not set\n");
        std::cerr << parser;
        return EXIT_FAILURE;
    }

    std::vector<std::string> header;
    std::string ip_network_dns_name;
    std::string file_name = "";

    if (Parsed_Arguments.list_filename.size() <= 0) {
        file_name = Parsed_Arguments.network + ".list";
    } else {
        file_name = Parsed_Arguments.list_filename;
    }
    std::string domain = Parsed_Arguments.domain;

    Tanja84dk::IP_Address Ip_Address_Obj(Parsed_Arguments.network);

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
    for (uint8_t i = 0; i < 255; i++) {
        header.push_back(gen_rev(i, Ip_Address_Obj, domain));
    }

    std::string rev_network =
        fmt::format("{0}.{1}.{2}", Ip_Address_Obj.get_third(), Ip_Address_Obj.get_second(), Ip_Address_Obj.get_first());

    std::string output_file_name = fmt::format("/buildtest/Cpp-Tanja84dk-DnsSync/pri.{0}.in-addr.arpa", rev_network);

    Tanja84dk::save_file(output_file_name, header);

    return 0;
}
