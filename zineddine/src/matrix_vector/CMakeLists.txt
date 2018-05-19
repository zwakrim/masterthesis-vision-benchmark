set(sources matrix_vector.cpp)
set(my_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_executable(matrix_vector ${sources})

target_include_directories(matrix_vector PRIVATE 
    ${OpenCL_INCLUDE_DIRS}
    ${my_include_dirs})

target_link_libraries(matrix_vector ${OpenCL_LIBRARIES})
