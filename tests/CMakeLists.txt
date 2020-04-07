#set(GTEST_ROOT ${EXTERNAL_LIBS_DIR}/test/googletest/googletest CACHE PATH "path to gtest")
#list(APPEND CMAKE_MODULE_PATH ${CONF_DIR})
#find_package(GTest1)


#message(${EXTERNAL_LIBS_DIR})

#if (NOT TARGET GTest::GTest)
#    message(FATAL_ERROR "Cannot find Google Test Framework!")
#endif()

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --coverage")
#message(FATAL_ERROR ${GTEST_INCLUDE_DIR})
file(GLOB TEST_SOURCE "*.cpp")
#file(GLOB SOURCE_FOR_TESTING "../src/grammar/*.cpp")
add_executable(Tests ${TEST_SOURCE})
target_link_libraries(Tests gtest gtest_main pthread GL::Grammar)
#target_include_directories(Test PRIVATE ${GTEST_INCLUDE_DIR})
#target_include_directories(Tests PRIVATE ${GTEST_INCLUDE_DIR})
#target_link_libraries(Tests GTest::GTest GTest::Main pthread GL::Grammar)
