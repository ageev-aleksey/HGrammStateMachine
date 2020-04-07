cmake_minimum_required(VERSION 3.0)

project(state_machine)

option(IS_TESTS "test compiling" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CONF_DIR ${PROJECT_SOURCE_DIR}/cmake)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(EXTERNAL_LIBS_DIR ${PROJECT_SOURCE_DIR}/external_libs)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)

include(${CONF_DIR}/Config.cmake)


if(${GNU})
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --Wall --Werror ")
endif()

add_subdirectory(${EXTERNAL_LIBS_DIR}/main/bprinter)
include_directories(${EXTERNAL_LIBS_DIR}/main/bprinter/include)
add_subdirectory(${SOURCE_DIR})

if(${IS_TESTS})	

add_subdirectory(${EXTERNAL_LIBS_DIR}/tests/googletest/googletest)
include_directories(${EXTERNAL_LIBS_DIR}/tests/googletest/googletest/include)
add_subdirectory(${TESTS_DIR})

endif()





