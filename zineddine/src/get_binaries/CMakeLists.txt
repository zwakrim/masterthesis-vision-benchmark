set(sources get_binaries.cpp)
set(my_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_executable(get_binaries ${sources})

target_include_directories(get_binaries PRIVATE 
    ${OpenCL_INCLUDE_DIRS}
    ${my_include_dirs})

target_link_libraries(get_binaries ${OpenCL_LIBRARIES})
