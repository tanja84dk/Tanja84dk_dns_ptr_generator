cmake_minimum_required(VERSION 3.16)
project(tanja84dk_dns_ptr_zone_generator
    LANGUAGES CXX
    VERSION 0.1.0
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

include(cmake/tanja84dk_generate_licenses.cmake)
tanja84dk_generate_license_begin()

set(${PROJECT_NAME}_SOURCES
    src/main.cpp
    src/dns_thing.cpp
    src/tools.cpp
    src/license.cpp
    src/license_helper.h
)

set(${PROJECT_NAME}_HEADERS
    include/tanja84dk/classes.h
    include/tanja84dk/dns_thing.h
    include/tanja84dk/license.h
    include/tanja84dk/tools.h
)

set(${PROJECT_NAME}_INTERNAL_HEADERS
    src/classes.h
)

set(${PROJECT_NAME}_LIBRARIES
    fmt
)

find_package(fmt REQUIRED)

tanja84dk_generate_license_manual(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
tanja84dk_generate_license_manual(fmt ${fmt_SOURCE_DIR}/LICENSE)

tanja84dk_generate_license_end()

configure_file(${${PROJECT_NAME}_LICENSES_MACRO_FILE} include/tanja84dk_licenses_macro.h)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        CXX_STANDARD 17
        VERSION ${${PROJECT_NAME}_VERSION}
    FOLDER
        Application
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${fmt_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${${PROJECT_NAME}_LIBRARIES}
    -static-libgcc -static-libstdc++ -static
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${WERROR_FLAG}
        ${PEDANTIC_COMPILE_FLAGS}
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)
