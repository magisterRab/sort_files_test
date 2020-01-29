

#LIBS
set(PROJECT_LIBS 
    ${CMAKE_THREAD_LIBS_INIT}
    rt.a
    m.a
    z.a
    )


#APP
add_executable(${PROJECT_NAME}_priority main.cpp)
target_link_libraries(${PROJECT_NAME}_priority ${PROJECT_LIBS})
