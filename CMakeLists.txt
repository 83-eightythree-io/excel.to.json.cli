cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
project(course)

find_package(RapidJSON REQUIRED)
include_directories(${RapidJSON_INCLUDE_DIR})

find_package(LibXslt REQUIRED)
include_directories(${LibXslt_INCLUDE_DIR})

find_package(RapidXML REQUIRED)

find_package(xlsxio CONFIG REQUIRED)

add_executable(course main.cpp)
target_link_libraries(course PRIVATE LibXslt::LibXslt)
target_link_libraries(course PRIVATE rapidjson)
target_link_libraries(course PRIVATE RapidXML::RapidXML)
target_link_libraries(course PRIVATE xlsxio::xlsxio_read_STATIC xlsxio::xlsxio_write_STATIC)
