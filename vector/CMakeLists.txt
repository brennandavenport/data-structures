cmake_minimum_required(VERSION 4.2)
project(vector_tests LANGUAGES CXX)

# interface bc header only
add_library(bd_vector_lib INTERFACE)

target_include_directories(bd_vector_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# add gtest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
option(ENABLE_ASAN "Enable AddressSanitizer" ON)

# create test exe
add_executable(vector_tests vector_tests.cpp)
target_link_libraries(vector_tests PRIVATE bd_vector_lib GTest::gtest_main)

if(ENABLE_ASAN)
    target_compile_options(vector_tests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(vector_tests PRIVATE -fsanitize=address,undefined)
endif()


include(GoogleTest)
gtest_discover_tests(vector_tests)

