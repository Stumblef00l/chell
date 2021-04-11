cmake_minimum_required(VERSION 3.20)

# Set the project name
project(wish VERSION 0.3)

# Header file for version
configure_file(config.h.in config.h @ONLY)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sources 
file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/include/*.hpp
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/builtin/*.cpp
    ${PROJECT_SOURCE_DIR}/include/builtin/*.hpp
)

# Compiler flags
set(CFLAGS "-g" "-Wall" "-Werror")

# C++ Standard libraries
set(STDLIBS)

# add executable
add_executable(wish main.cpp config.build.cpp ${SOURCES})

# Configured files are written into the binary tree, must add into the include path
target_include_directories(wish PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/include)

# Compiler flags
target_compile_options(wish PUBLIC ${CFLAGS})

# Link libraries
target_link_libraries(wish PUBLIC ${STDLIBS})

# Output directory for binary
set_target_properties(wish
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# ---- Tests -------

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES
    tests/*.cpp
)

set(TEST_LIBS gtest_main)

enable_testing()

add_executable(test_wish ${TEST_SOURCES} ${SOURCES})
target_include_directories(test_wish 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
)
set_target_properties(test_wish
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)
target_link_libraries(test_wish ${TEST_LIBS})

include(GoogleTest)
gtest_discover_tests(test_wish)
