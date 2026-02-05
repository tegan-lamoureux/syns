# Note (Tegan): I took the base of this CMake config from Google.
# https://google.github.io/googletest/quickstart-cmake.html 

cmake_minimum_required(VERSION 3.14)
project(syns_question_3_4)

cmake_policy(SET CMP0135 NEW) # Suppress error from google's config

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  linked_list_tests
  
  src/linked_list.cpp

  tests/car_tests.cpp
  tests/linked_list_tests.cpp
  tests/sort_tests.cpp
)

target_include_directories(
    linked_list_tests PUBLIC

    src/
)

target_link_libraries(
  linked_list_tests
  
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(linked_list_tests)