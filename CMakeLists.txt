cmake_minimum_required(VERSION 3.4)

project(WorkWithGtest)

add_subdirectory(
	"${CMAKE_CURRENT_SOURCE_DIR}/gtest"
	"gtest"
)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/banking
)

add_executable(
	testBanking
	tests/testBanking.cpp
)

target_include_directories(
	testBanking PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/banking"
)


target_link_libraries(
	testBanking PRIVATE
	gtest gtest_main banking
)

target_compile_options(
	testBanking PRIVATE
	-Wall -Wextra -pedantic -Werror
)




