file (GLOB SOURCE *.cpp)

add_executable(${PROJECT} ${SOURCE})
target_include_directories(${PROJECT} ${INCLUDE_DIR} ${RapidJSON_INCLUDE_DIR})
