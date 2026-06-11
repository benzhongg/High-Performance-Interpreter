add_executable(VirtualMachineTest 
    #fileReaderTest.cpp 
    # injectorTest.cpp 
    instructionBuilderTest.cpp 
    # instructionTest.cpp 
    #interpreterTest.cpp
    )

target_link_libraries(VirtualMachineTest PRIVATE LIBRARY GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(VirtualMachineTest)
