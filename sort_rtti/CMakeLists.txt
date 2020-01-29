

#LIBS
set(PROJECT_LIBS 
    ${CMAKE_THREAD_LIBS_INIT}
    rt.a
    m.a
    z.a
    )


# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti")

#APP
add_executable(${PROJECT_NAME}_rtti main.cpp)
target_link_libraries(${PROJECT_NAME}_rtti ${PROJECT_LIBS})
