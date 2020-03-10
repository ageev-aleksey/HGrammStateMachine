file(GLOB SOURCE *.cpp ./grammar/*.cpp ./grammar/exeption/*.cpp)
add_executable(app ${SOURCE})
#add_executable(app ./Main.cpp ./grammar/Symbol.cpp)
target_include_directories(app PRIVATE ${INCLUDE_DIR} ${RapidJSON_INCLUDE_DIR})
