# Tanja84dk_dns_ptr_generator

## Info

### Usage

The program is made to generate reverse dns/PTR zone for bind9 since I often felt it were tedious to create all the records with almost identical info line by line

so the way to use it is to run it with the options --network and --domain for it to generate the zone file.

If you have some host where you know the hostname for then it's possible to enter them into a text file named network_ip.list ( so as an example 10.10.10.0.list ) in the current directory since that is the default filename schema it's looking for.

For any ip that it don't find in a file it will then just create a ptr entry with the hostname ip_with_dash.dyn.domain.

So lets say we ran it with --domain home.example.local --network 10.10.10.0, then it would make the records with the hostname like 10-10-10-2.dyn.home.example.local.

if a entry in a file is found then it would just the hostname.domain. instead of the default

Also if there is entered a . after the hostname in the list file then it would see it as a fully qualified dns name and not append the .domain. to the entry

It will also save the zone file to a file in the current folder named pri.10.10.10.in-addr.arpa ( in the example of network is 10.10.10.0 )

## Used External libraries

- [**_argparse_**](https://github.com/p-ranav/argparse) created by [**_Pranav_**](https://github.com/p-ranav)
- [**_fmtlib_**](https://github.com/fmtlib/fmt) created by [**_fmtlib_**](https://github.com/fmtlib)

## Used third-party tools

- [**_CPM.cmake_**](https://github.com/cpm-cmake/CPM.cmake) version 0.40.5 for getting and manage libraries
- [**_Clang_**](https://clang.llvm.org) for compilation with code sanitizers
- [**_CMake_**](https://cmake.org) for build automation

## License

See the 'LICENSE' for details. In summary Tanja84dk_dns_ptr_generator is licensed under the MIT License.

## Additional Licenses

- [**_CPM.cmake_**]() maintained by [**_cpm-cmake_**](https://github.com/cpm-cmake) is licensed under [**_MIT License_**](https://github.com/cpm-cmake/CPM.cmake/blob/cd28d445aeb4cecd9d10d63a55a52bcbdd8bf17e/LICENSE)
- [**_argparse_**](https://github.com/p-ranav/argparse) created by [**_Pranav_**](https://github.com/p-ranav) is licensed under [**_MIT License_**](https://github.com/p-ranav/argparse/blob/v3.2/LICENSE)
- [**_fmtlib_**](https://github.com/fmtlib/fmt) created by [**_fmtlib_**](https://github.com/fmtlib) in licensed under [**_MIT License_**](https://github.com/fmtlib/fmt/blob/9cf9f38eded63e5e0fb95cd536ba51be601d7fa2/LICENSE)
