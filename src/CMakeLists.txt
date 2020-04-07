file(GLOB SOURCE ./regex/*.cpp)
add_library(Grammar ${SOURCE})
add_library(GL::Grammar ALIAS Grammar)
add_executable(app ./Main.cpp ./grammar/Symbol.cpp)
target_include_directories(app PRIVATE ${INCLUDE_DIR})
target_include_directories(Grammar PUBLIC ${INCLUDE_DIR})

target_link_libraries(app PUBLIC Grammar bprinter)
