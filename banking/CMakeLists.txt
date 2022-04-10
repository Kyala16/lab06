cmake_minimum_required(VERSION 3.4)

project(Bank)

add_library(
	banking STATIC
		Account.cpp
		Account.h
		Transaction.cpp
		Transaction.h
)

set_target_properties(
	banking PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED oN
)


