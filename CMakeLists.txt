cmake_minimum_required(VERSION 3.5)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_subdirectory( gtest )
enable_testing()

include_directories(${gtest_SOURCE_DIR}/googletest/include })

add_executable(runUnitTests src/hello_lua.cpp)

target_link_libraries(runUnitTests gtest gtest_main lua)
