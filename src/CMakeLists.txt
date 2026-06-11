set(SOURCES
    fileReader.cpp
    injector.cpp
    injector.cpp
    instruction.cpp
    instructionBuilder.cpp
    interpreter.cpp
)

add_library(LIBRARY ${SOURCES})
target_include_directories(LIBRARY PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(High-Performance-Interpreter main.cpp)

target_link_libraries(High-Performance-Interpreter PRIVATE LIBRARY)

