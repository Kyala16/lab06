#include <iostream>
#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>

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


