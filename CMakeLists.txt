# Inspired by: https://github.com/Ashe/Relocate-Engine/blob/master/CMakeLists.txt
cmake_minimum_required (VERSION 3.7)
project (FourInARow)

message("Using CMake version ${CMAKE_VERSION}")
message("Processing CMakeLists.txt")

# Compiler version
set (CMAKE_CXX_STANDARD 17)

# Define location for modules
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules/)
message("Module path: ${CMAKE_MODULE_PATH}")

# Specify where these packages are installed
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "./SFML-2.5.1/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5.1 REQUIRED COMPONENTS window system graphics audio network)

# Define sources
file(GLOB_RECURSE SRCS 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# Create the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable (${EXECUTABLE_NAME} ${SRCS})

# Link libraries so that they can be used in the project
target_link_libraries(${EXECUTABLE_NAME}
  sfml-window
  sfml-system
  sfml-graphics
)

# Copy assets
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
