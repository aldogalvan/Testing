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

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
include(libigl)

# header search path
include_directories (${PROJECT_SOURCE_DIR}/src)

#add executable
add_executable(Testing src/main.cpp src/TetMesh.cpp src/GenericObject.cpp src/ToolObject.cpp src/TriMesh.cpp src/World.cpp src/World.h src/GenericMesh.cpp src/GenericMesh.h src/GenericConstrants.h src/ExtendedConstraints.h src/CollisionDetector.cpp src/CollisionDetector.h src/HDCallbacks.cpp src/HDCallbacks.h)

#link library
target_link_libraries(Testing PRIVATE ${VTK_LIBRARIES} Eigen3::Eigen -lHDU -lHD -lrt -lstdc++ -lm)
target_link_libraries(Testing PUBLIC igl::core igl::opengl_glfw)


