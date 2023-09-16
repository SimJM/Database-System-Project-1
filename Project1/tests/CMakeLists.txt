cmake_minimum_required(VERSION 3.12)
project(YourTestProjectName)

# Add your test executable
add_executable(RecordTest src/RecordTest.cpp)

# Link Catch2 to your test executable
target_link_libraries(RecordTest PRIVATE Catch2::Catch2)

# This is where you specify the source directory for your project
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Include your project source directory
target_include_directories(RecordTest PRIVATE ${PROJECT_SOURCE_DIR})

# Add your project's source files (if needed)
# target_sources(RecordTest PRIVATE ${PROJECT_SOURCE_DIR}/YourSourceFile.cpp)

# Add a test target
include(CTest)
include(Catch)
catch_discover_tests(RecordTest)