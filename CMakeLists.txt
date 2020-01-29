cmake_minimum_required( VERSION 3.4.0 )


project(sort_files)

set(CMAKE_CXX_STANDARD 17)

# Check path for external libs
if(DEFINED EXTERNAL_LIBS_PATH)
    message("Use ${EXTERNAL_LIBS_PATH} as path for external libs")

    include_directories(SYSTEM ${EXTERNAL_LIBS_PATH}/include)
    link_directories(${EXTERNAL_LIBS_PATH}/lib)
    list(APPEND CMAKE_FIND_ROOT_PATH ${EXTERNAL_LIBS_PATH})
    list(APPEND CMAKE_MODULE_PATH ${EXTERNAL_LIBS_PATH}/cmake)
endif()


# Check path for sniper libs
if(DEFINED SNIPER_LIBS_PATH)
    message("Use ${SNIPER_LIBS_PATH} as path for sniper libs")

    include_directories(SYSTEM ${SNIPER_LIBS_PATH}/include)
    link_directories(${SNIPER_LIBS_PATH}/lib)
    list(APPEND CMAKE_FIND_ROOT_PATH ${SNIPER_LIBS_PATH})
    list(APPEND CMAKE_MODULE_PATH ${SNIPER_LIBS_PATH}/cmake)
endif()


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
