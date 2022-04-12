/*#include <iostream>
#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct MockTrans : public Transaction{
    MOCK_METHOD3(Make, bool(Account& from, Account& to, int sum));
    MOCK_METHOD1(set_fee, void(int fee));
    MOCK_METHOD0(fee, int());
};

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

TEST(Transaction, TransMockTest1){
    MockTrans Acc_Trans1;
    MockAcc Human1(1, 10000);
    MockAcc Human2(2, 230000);
    MockAcc Car_Shop(3, 8000000);
    MockAcc Organisation(4, 5500);
    EXPECT_CALL(Acc_Trans1, set_fee(testing::_)).Times(1);
    EXPECT_CALL(Acc_Trans1, Make(testing::_, testing::_, testing::_)).Times(2);
    EXPECT_CALL(Acc_Trans1, fee()).Times(1);
    EXPECT_CALL(Human1, GetBalance()).Times(1);
    EXPECT_CALL(Human2, GetBalance()).Times(1);
    Acc_Trans1.set_fee(500);
    Acc_Trans1.Make(Human1, Human2, 2000);
    Acc_Trans1.fee();
    Human1.GetBalance();
    Human2.GetBalance();
    Acc_Trans1.Make(Organisation, Human2, 20000);
}

TEST(Transaction, TransMockTest2){
    MockTrans Acc_Trans2;
    MockAcc Human1(1, 10000);
    MockAcc Human2(2, 230000);
    MockAcc Car_Shop(3, 8000000);
    MockAcc Organisation(4, 5500);
    EXPECT_CALL(Acc_Trans2, Make(testing::_, testing::_, testing::_)).Times(3);
    Acc_Trans2.Make(Car_Shop, Car_Shop, 100000);
    Acc_Trans2.Make(Car_Shop, Organisation, -5600);
    Acc_Trans2.Make(Human2, Car_Shop, 55);
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

}*/

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

TEST(Account, AccMockTest1){
    MockAcc BankAccount(1, 15000);
    EXPECT_CALL(BankAccount, ChangeBalance(testing::_)).Times(1);
    EXPECT_CALL(BankAccount, GetBalance()).Times(2);
    EXPECT_CALL(BankAccount, id()).Times(2);
    EXPECT_CALL(BankAccount, Lock()).Times(1);
    BankAccount.GetBalance();
    BankAccount.id();
    BankAccount.Lock();
    BankAccount.ChangeBalance(5000);
    BankAccount.GetBalance();
    BankAccount.id();
}

TEST(Account, AccMockTest2){
    MockAcc BankAccount2(2, 100000);
    EXPECT_CALL(BankAccount2, Lock()).Times(1);
    EXPECT_CALL(BankAccount2, GetBalance()).Times(2);
    EXPECT_CALL(BankAccount2, ChangeBalance(testing::_)).Times(2);
    EXPECT_CALL(BankAccount2, Unlock()).Times(1);
    BankAccount2.Lock();
    BankAccount2.GetBalance();
    BankAccount2.ChangeBalance(100000);
    BankAccount2.GetBalance();
    BankAccount2.Unlock();
    BankAccount2.ChangeBalance(1000);
}


TEST(Account, GetBalance_and_ID){
    Account BankAccount(1, 15000);

    EXPECT_EQ(BankAccount.GetBalance(), 15000);
    EXPECT_EQ(BankAccount.id(), 1);

    BankAccount.Lock();
    BankAccount.ChangeBalance(5000);

    EXPECT_EQ(BankAccount.GetBalance(), 20000);
    EXPECT_EQ(BankAccount.id(), 1);
}

TEST(Account, ChangeBalance_and_Lock){
    Account BankAccount2(2, 100000);
    BankAccount2.Lock();

    EXPECT_EQ(BankAccount2.GetBalance(), 100000);

    BankAccount2.ChangeBalance(100000);

    EXPECT_EQ(BankAccount2.GetBalance(), 200000);

    BankAccount2.Unlock();
    ASSERT_ANY_THROW(BankAccount2.ChangeBalance(1000));
}

TEST(Transaction, TransMockTest1){
    MockTrans Acc_Trans1;
    MockAcc Human1(1, 10000);
    MockAcc Human2(2, 230000);
    MockAcc Car_Shop(3, 8000000);
    MockAcc Organisation(4, 5500);
    EXPECT_CALL(Acc_Trans1, set_fee(testing::_)).Times(1);
    EXPECT_CALL(Acc_Trans1, Make(testing::_, testing::_, testing::_)).Times(2);
    EXPECT_CALL(Acc_Trans1, fee()).Times(1);
    EXPECT_CALL(Human1, GetBalance()).Times(1);
    EXPECT_CALL(Human2, GetBalance()).Times(1);
    Acc_Trans1.set_fee(500);
    Acc_Trans1.Make(Human1, Human2, 2000);
    Acc_Trans1.fee();
    Human1.GetBalance();
    Human2.GetBalance();
    Acc_Trans1.Make(Organisation, Human2, 20000);
}

TEST(Transaction, TransMockTest2){
    MockTrans Acc_Trans2;
    MockAcc Human1(1, 10000);
    MockAcc Human2(2, 230000);
    MockAcc Car_Shop(3, 8000000);
    MockAcc Organisation(4, 5500);
    EXPECT_CALL(Acc_Trans2, Make(testing::_, testing::_, testing::_)).Times(3);
    Acc_Trans2.Make(Car_Shop, Car_Shop, 100000);
    Acc_Trans2.Make(Car_Shop, Organisation, -5600);
    Acc_Trans2.Make(Human2, Car_Shop, 55);
}

TEST(Transaction, Make){
    Transaction Acc_Trans;

    Account Human1(1, 10000);
    Account Human2(2, 230000);
    Account Car_Shop(3, 8000000);
    Account Organisation(4, 5500);

    Acc_Trans.set_fee(500);
    Acc_Trans.Make(Human1, Human2, 2000);

    EXPECT_NE(Acc_Trans.fee(), 350);
    EXPECT_EQ(Human1.GetBalance(), 7500);
    EXPECT_EQ(Human2.GetBalance(), 232000);
    ASSERT_EQ(Acc_Trans.Make(Organisation, Human2, 20000), false);
}

TEST(Transaction, MakeExceptions){
    Transaction Acc_Trans;

    Account Human1(1, 10000);
    Account Human2(2, 230000);
    Account Car_Shop(3, 8000000);
    Account Organisation(4, 5500);

    ASSERT_ANY_THROW(Acc_Trans.Make(Car_Shop, Car_Shop, 100000));
    ASSERT_ANY_THROW(Acc_Trans.Make(Car_Shop, Organisation, -5600));
    ASSERT_ANY_THROW(Acc_Trans.Make(Human2, Car_Shop, 55));
}


