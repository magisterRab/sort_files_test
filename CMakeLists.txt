cmake_minimum_required( VERSION 3.4.0 )


project(sort_files)

set(CMAKE_CXX_STANDARD 17)


# Load modules
find_package(Threads)


# Include local libs for macos x ports
include_directories("/opt/local/include")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-inline")

add_subdirectory(sort_priority)
add_subdirectory(sort_name)
add_subdirectory(sort_rtti)
add_subdirectory(sort_priority_external)
add_subdirectory(sort_name_external)
add_subdirectory(sort_rtti_external)
add_subdirectory(sort_multiple_dispatch)
add_subdirectory(sort_multiple_dispatch_2)
add_subdirectory(sort_multiple_dispatch_with_priority)
add_subdirectory(sort_multiple_dispatch_external_priority)
