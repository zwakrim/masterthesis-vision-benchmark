set(sources erosion.cpp)
set(my_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_executable(erosion ${sources})

target_include_directories(erosion PRIVATE 
    ${OpenCL_INCLUDE_DIRS}
    ${my_include_dirs})

target_link_libraries(erosion ${OpenCL_LIBRARIES})
