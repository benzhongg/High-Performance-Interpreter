add_executable(VirtualMachineTest 
    fileReaderTest.cpp 
    # injectorTest.cpp 
    # instructionBuilderTest.cpp
    # mainTest.cpp 
    # instructionTest.cpp 
    #interpreterTest.cpp
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/testData.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/testData.txt"
    COPYONLY
)

target_link_libraries(VirtualMachineTest PRIVATE 
    LIBRARY 
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(VirtualMachineTest)
