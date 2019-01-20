cmake_minimum_required(VERSION 3.8)
project(ModernCpp)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(/usr/local/Cellar/boost/1.65.1/include)

set(SOURCE_FILES
        main.cpp
        Test/AlgorithmTest.cpp
        Test/ClassesTest.cpp
        Test/GenericProgrammingTest.cpp
        Test/meta_test.cpp
        Test/MetaProgrammingTest.cpp
        Test/MoveSemanticsTest.cpp
        Test/sfinae_test.cpp
        Test/UniquePtr.cpp
        Test/VariadicTemplateTest.cpp Test/ExpressionTemplateTest.cpp Test/RootFindingTest.cpp Test/MetaTuningTest.cpp
        Test/EnableTest.cpp Test/FunctionTemplateTest.cpp Test/ClassTemplateTEst.h Test/VariousOverload.cpp Test/TagDispatchTest.cpp Test/MetaFunctionsTest.cpp Test/PolicyTest.cpp Test/Enable_if_function_test.cpp Test/CRTPTest.cpp Test/PolymorphicTest.cpp Test/TypeErasureTest.cpp Test/AnyTest.cpp Test/ConceptOfMin.cpp Test/ConceptOfPoint.cpp Test/ConceptOfFTest.cpp Test/ConceptOverload.cpp Test/ConceptOfNorm.cpp Test/MetaFunctions2Test.cpp Test/IteratorTest.cpp Test/IteratorAdapterTest.cpp Test/enable_if_class_Test.cpp)

add_executable(ModernCpp ${SOURCE_FILES})
target_link_libraries(ModernCpp gtest_main)
target_link_libraries(ModernCpp gmock_main)