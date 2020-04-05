
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests/googletest/googletest)
#add_library(GTEST::GTEST ALIAS gtest)
#add_library(GTEST::MAIN ALIAS gtest_main)

#find_path(GTEST_INCLUDE_DIR
        #NAMES "gtest.h"
        #PATHS ${GTEST_ROOT}/include/gtest
       # )

set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
message(STATUS "Gtest Root => ${GTEST_ROOT}")
message(STATUS "gtest/gtest.h => ${GTEST_INCLUDE_DIR}")

if(GTEST_INCLUDE_DIR)
    find_library(GTEST_LIB
            NAMES gtest libgtest
            HINTS ${GTEST_ROOT}/lib
            )
    find_library(GTEST_LIB_MAIN
            NAMES gtest_main libgtest_main
            HINTS ${GTEST_ROOT}/lib
            )
    if(${GTEST_LIB} STREQUAL "GTEST_LIB-NOTFOUND")
    	message(STATUS "Gtest not found - start download source from github")
    	execute_process(COMMAND git submodule update --init -- external_lib/gtest
                    	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    endif()
    message(STATUS " Gtest Libs:")
    message(STATUS "> " ${GTEST_LIB})
    message(STATUS "> " ${GTEST_LIB_MAIN})


    add_library(GTest::GTest UNKNOWN IMPORTED)
    add_library(GTest::Main UNKNOWN IMPORTED)
    set_target_properties(GTest::GTest PROPERTIES
            IMPORTED_LOCATION ${GTEST_LIB}
            #INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIR}
            INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIR})
    set_target_properties(GTest::Main PROPERTIES
            IMPORTED_LOCATION  ${GTEST_LIB_MAIN}
            #INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIR})
            INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIR})
endif()
