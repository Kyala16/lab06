# lab06

Status of Last Build:<br>
<img src="https://github.com/Kyala16/lab06/workflows/CI/badge.svg?branch=main"><br>

[![Coverage Status](https://coveralls.io/repos/github/Kyala16/lab06/badge.svg)](https://coveralls.io/github/Kyala16/lab06)

## build CMake for bankind lib

![This is an image](/pic/1.png)
![This is an image](/pic/2.png)

______________________________________________________________________________________________________________________________

## Test build

```
#include <iostream>
#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct MockAcc : public Account{
    MockAcc(int id, int balance) : Account(id, balance){}
    MOCK_METHOD1(ChangeBalance, void(int diff));
    MOCK_METHOD0(GetBalance, int());
    MOCK_METHOD0(id, int());
    MOCK_METHOD0(Lock, void());
    MOCK_METHOD0(Unlock, void());
};

struct MockTrans : public Transaction{
    MOCK_METHOD3(Make, bool(Account& from, Account& to, int sum));
    MOCK_METHOD1(set_fee, void(int fee));
    MOCK_METHOD0(fee, int());
};

TEST(Account, AccMockTest){
    MockAcc Bank(2, 100000);
    EXPECT_CALL(Bank, Lock()).Times(1);
    EXPECT_CALL(Bank, GetBalance()).Times(2);
    EXPECT_CALL(Bank, ChangeBalance(testing::_)).Times(2);
    EXPECT_CALL(Bank, Unlock()).Times(1);
    Bank.Lock();
    Bank.GetBalance();
    Bank.ChangeBalance(100000);
    Bank.GetBalance();
    Bank.Unlock();
    Bank.ChangeBalance(1000);
}

TEST(Account, Lock){
	Account store_bank(105, 150000);
	store_bank.Lock();
	
	ASSERT_NO_THROW(store_bank.ChangeBalance(100000));
	EXPECT_EQ(store_bank.GetBalance(),250000);
	ASSERT_NO_THROW(store_bank.ChangeBalance(-100000));
	EXPECT_EQ(store_bank.GetBalance(),150000);
	
	store_bank.Unlock();

	ASSERT_ANY_THROW(store_bank.ChangeBalance(100000));
	ASSERT_NO_THROW(store_bank.GetBalance());
}

TEST(Account, ChangeBalance){
	Account store_bank(44,1500000);
	Account car_bank(25,12000);
	store_bank.Lock();
	car_bank.Lock();

	EXPECT_EQ(store_bank.GetBalance(),1500000);
	EXPECT_EQ(store_bank.id(),44);

	store_bank.ChangeBalance(6886);

	EXPECT_EQ(store_bank.GetBalance(),1506886);
	EXPECT_EQ(store_bank.id(),44);

	car_bank.ChangeBalance(0);

	ASSERT_NO_THROW(car_bank.ChangeBalance(0));
	EXPECT_EQ(car_bank.GetBalance(),12000);

	store_bank.Unlock();
	car_bank.Unlock();
}

TEST(Transaction, TransMockTest){
    MockTrans Acc_Trans1;
    MockAcc son(1, 10000);
    MockAcc dad(2, 230000);
    MockAcc Car_Shop(3, 8000000);
    MockAcc Organisation(4, 5500);
    EXPECT_CALL(Acc_Trans1, set_fee(testing::_)).Times(1);
    EXPECT_CALL(Acc_Trans1, Make(testing::_, testing::_, testing::_)).Times(2);
    EXPECT_CALL(Acc_Trans1, fee()).Times(1);
    EXPECT_CALL(son, GetBalance()).Times(1);
    EXPECT_CALL(dad, GetBalance()).Times(1);
    Acc_Trans1.set_fee(500);
    Acc_Trans1.Make(son, dad, 2000);
    Acc_Trans1.fee();
    son.GetBalance();
    dad.GetBalance();
    Acc_Trans1.Make(Organisation, dad, 20000);
}

TEST(Transaction, Throws){
	Transaction bank;

	Account dad(1, 1500000);
	Account son(2, 1000);
	Account student(3, 10);
	Account university(666, 8450000);

	ASSERT_ANY_THROW(bank.Make(dad,dad,1001));
	ASSERT_ANY_THROW(bank.Make(university,student,-1000));
	ASSERT_ANY_THROW(bank.Make(university,student, 10));
	ASSERT_NO_THROW(bank.Make(dad,son,1000));
}

TEST(Transaction, Make){
	Transaction bank;

	Account dad(1,1500000);
	Account son(2,1222);
	

	EXPECT_EQ(bank.fee(),1);
	bank.set_fee(0);
	ASSERT_NO_THROW(bank.Make(dad,son,10000));
	ASSERT_NO_THROW(bank.Make(son,dad,10000));
	bank.set_fee(1);
	EXPECT_EQ(bank.fee(),1);
	ASSERT_EQ(bank.Make(dad,son,10000),true);
	EXPECT_EQ(son.GetBalance(),11222);
	EXPECT_EQ(dad.GetBalance(),1489999);
	EXPECT_EQ(son.GetBalance(),11222);
	
	ASSERT_EQ(bank.Make(son,dad,100000),false);
}

TEST(Transaction, Set_fee){
	Transaction bank;

	Account student(1,25000);
	Account university(2,2500000);

	EXPECT_EQ(bank.fee(),1);
	bank.set_fee(1000);
	ASSERT_EQ(bank.Make(university,student,4300),true);
	EXPECT_EQ(university.GetBalance(),2494700);
	EXPECT_EQ(student.GetBalance(),29300);

	bank.set_fee(0);
	ASSERT_EQ(bank.Make(university,student,10000),true);
	EXPECT_EQ(university.GetBalance(),2484700);
	EXPECT_EQ(student.GetBalance(),39300);

}
```
_____________________________________________________________________________________

```
#-------------------------------------
#  Lab06 - Work this GitHub Actions
#  @Kyala16
#-------------------------------------

name: bank

on:
  push:
    branches: main

  workflow_dispatch:

jobs:
  build_lib:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v2

      - name: Build banking_lib
        shell: bash
        run: |
          cd banking
          mkdir built && cd built
          cmake ..
          cmake --build .
          
  Test_banking:
    runs-on: ubuntu-latest
    
    steps:
      - uses: actions/checkout@v2
      
      - name: prepare environment
        run:  |
              sudo apt install git && git submodule update --init
              sudo apt install lcov
              sudo apt install g++-7
      
      - name: Test
        run: |
          mkdir built && cd built
          CXX=/usr/bin/g++-7 cmake -DCOVERAGE=1 ..
          cmake --build .
          ./testBanking
          lcov -t "banking" -o lcov.info -c -d .
      - name: Coveralls Parallel
        uses: coverallsapp/github-action@master
        with:
          github-token: ${{ secrets.github_token }}
          parallel: true
          path-to-lcov: ./built/lcov.info
          coveralls-endpoint: https://coveralls.io

      - name: Coveralls Finished
        uses: coverallsapp/github-action@master
        with:
          github-token: ${{ secrets.github_token }}
          parallel-finished: true
```
_____________________________________________________________________________________

```
cmake_minimum_required(VERSION 3.4)
SET(COVERAGE OFF CACHE BOOL "Coverage")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

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

if (COVERAGE)
    target_compile_options(testBanking PRIVATE --coverage)
    target_link_libraries(testBanking PRIVATE --coverage)
endif()

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

```
