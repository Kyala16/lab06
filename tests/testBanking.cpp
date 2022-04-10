#include <iostream>
#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>

TEST(Account, Lock){
	Account store_bank(105, 150000);
	store_bank.Lock();
	
	ASSERT_NO_THROW(store_bank.ChangeBalance(100000));
	
	store_bank.Unlock();

	ASSERT_ANY_THROW(store_bank.ChangeBalance(100000));
}

TEST(Account, ChangeBalance){
	Account store_bank(44,1500000);
	store_bank.Lock();

	EXPECT_EQ(store_bank.GetBalance(),1500000);
	EXPECT_EQ(store_bank.id(),44);

	store_bank.ChangeBalance(6886);

	EXPECT_EQ(store_bank.GetBalance(),1506886);
	EXPECT_EQ(store_bank.id(),44);

	store_bank.Unlock();
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
}

TEST(Transaction, Make){
	Transaction bank;

	Account dad(1,1500000);
	Account son(2,1222);

	ASSERT_EQ(bank.Make(dad,son,10000),true);
	EXPECT_EQ(son.GetBalance(),11222);
	EXPECT_EQ(dad.GetBalance(),1489999);
	
	ASSERT_EQ(bank.Make(son,dad,100000),false);
}

