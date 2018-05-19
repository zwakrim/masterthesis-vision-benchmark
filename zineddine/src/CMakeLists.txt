cmake_minimum_required(VERSION 3.7)
project(opencl-code CXX)

find_package(OpenCL REQUIRED)

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin )

add_subdirectory(platforms_devices)
add_subdirectory(get_binaries)
add_subdirectory(simple_opencl)
add_subdirectory(opencl_events)
add_subdirectory(workspace_query)
add_subdirectory(matrix_vector)
add_subdirectory(erosion)
