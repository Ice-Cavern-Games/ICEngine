cmake_minimum_required(VERSION 3.21)
project(TestApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Include ICEngine
add_subdirectory(
    ../../          # source_dir
    ../../../build  # binary_dir
)

# Executable
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Reference ICEngine
target_link_libraries(${PROJECT_NAME} PRIVATE IceCavernEngine)
