cmake_minimum_required(VERSION 3.30.3)

project(makic VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../bin")

set(COMPILER_SRC
    src/util.c
    src/console.c
    src/makic.c
    src/builder.c
    src/lexer.c
)

add_executable(${PROJECT_NAME} ${COMPILER_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_compile_options(${PROJECT_NAME} PRIVATE -Wno-trigraphs)