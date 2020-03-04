file(GLOB SOURCE *.cpp ./grammar/*.cpp)
add_executable(app ${SOURCE})
target_include_directories(app PRIVATE ${INCLUDE_DIR} ${RapidJSON_INCLUDE_DIR})
