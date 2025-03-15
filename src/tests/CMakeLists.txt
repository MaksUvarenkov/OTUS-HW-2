add_executable(test_main main.cpp
        TestData.cpp)

find_package(OpenSSL REQUIRED)

target_include_directories(test_main PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(test_main checker_lib)
target_link_libraries(test_main OpenSSL::Crypto)
target_link_libraries(test_main GTest::GTest GTest::Main)

add_test(NAME MyProjectTest COMMAND test_main)