cmake_minimum_required(VERSION 3.0)

project(state_machine)

option(IS_TESTS "test compiling" ON)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(EXTERNAL_LIBS_DIR ${PROJECT_SOURCE_DIR}/external_libs)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)


add_subdirectory(${EXTERNAL_LIBS_DIR}/main/rapidjson)
add_subdirectory(${SOURCE_DIR})

if(${IS_TESTS})	
add_subdirectory(${TESTS_DIR})
endif()





