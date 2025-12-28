cmake_minimum_required(VERSION 3.10)
project(FeelMeHappy VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(FEELMEHAPPY_BUILD_EXAMPLES "Build examples" ON)
option(FEELMEHAPPY_BUILD_TESTS "Build tests" ON)
option(FEELMEHAPPY_BUILD_BENCHMARKS "Build benchmarks" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(FeelMeHappy INTERFACE)
target_include_directories(FeelMeHappy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(FEELMEHAPPY_BUILD_EXAMPLES)
    add_executable(basic_example examples/basic_usage.cpp)
    target_link_libraries(basic_example FeelMeHappy)
    
    add_executable(advanced_example examples/advanced_usage.cpp)
    target_link_libraries(advanced_example FeelMeHappy)
    
    add_executable(android_example examples/android_example.cpp)
    target_link_libraries(android_example FeelMeHappy)
    
    if(ANDROID)
        target_compile_definitions(android_example PRIVATE FEELMEHAPPY_ANDROID)
    endif()
endif()

if(FEELMEHAPPY_BUILD_TESTS)
    add_executable(unit_tests tests/unit_tests.cpp)
    target_link_libraries(unit_tests FeelMeHappy)
    
    add_executable(performance_tests tests/performance_tests.cpp)
    target_link_libraries(performance_tests FeelMeHappy)
    
    if(FEELMEHAPPY_BUILD_BENCHMARKS)
        add_custom_target(run_benchmarks COMMAND performance_tests)
    endif()
    
    add_custom_target(run_tests COMMAND unit_tests)
endif()

install(TARGETS FeelMeHappy EXPORT FeelMeHappyTargets)
install(DIRECTORY include/ DESTINATION include)

if(FEELMEHAPPY_BUILD_EXAMPLES)
    install(TARGETS basic_example advanced_example android_example DESTINATION bin)
endif()

if(FEELMEHAPPY_BUILD_TESTS)
    install(TARGETS unit_tests performance_tests DESTINATION tests)
endif()
