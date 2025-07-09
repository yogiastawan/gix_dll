cmake_minimum_required(VERSION 3.10.0)

message(STATUS "Configuring test directory")
add_executable(gdll_test gdll_test.c)
target_link_libraries(gdll_test gix-dllist)

add_test(GDLL_TEST gdll_test)
