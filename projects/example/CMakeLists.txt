cmake_minimum_required(VERSION 3.10)
project(example VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_executable(example
    src/main.c
    src/helper.c
)

target_compile_options(example PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Optional: Enable testing
enable_testing()
add_subdirectory(tests)
