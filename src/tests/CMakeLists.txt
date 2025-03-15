add_executable(test_main main.cpp)

target_link_libraries(test_main GTest::GTest GTest::Main)

add_test(NAME MyProjectTest COMMAND test_main)