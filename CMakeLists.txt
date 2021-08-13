cmake_minimum_required(VERSION 3.20)
project(Testing)

set(CMAKE_CXX_STANDARD 14)

#set output location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
# Core libraries
# ==============

#Eigen
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

#VTK
set(VTK_DIR "/home/herolab/Downloads/build/")
find_package(VTK COMPONENTS REQUIRED)
include_directories (${VTK_INCLUDE_DIRS})
link_directories (${VTK_LIBRARY_DIRS})
add_definitions (${VTK_DEFINITIONS})

#incude directories
include_directories(${PROJECT_SOURCE_DIR}/src)

#add executable
add_executable(Testing main.cpp src/TetMesh.cpp src/GenericObject.cpp src/GenericObject.h)

#link library
target_link_libraries(Testing PRIVATE ${VTK_LIBRARIES} Eigen3::Eigen)


#automatically initiate the module
vtk_module_autoinit(

        TARGETS Testing
        MODULES ${VTK_LIBRARIES}
)

