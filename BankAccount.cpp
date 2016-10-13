#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>

//Answer to assignment quation:
//Polymorphism literally means "having many forms;"
//In the context of a C++ program, polymorphism refers to the
//existence of a hierarchy of classes all of which a interconnected via inheritance.
//Wheras, inheritance occurs when a new class inherits the characteristics of a base class. 
//This program incorporates 'BankAccount' attributes which are inherited throughout
//the program and used to connect a variety of classes. 


using namespace std;

class BankAccount {
protected:
	int accountNumber;
	double interestRate;
	double balance;
	string anykey = " ";

public:
	BankAccount(int accountNumber, double interestRate, double balance) :
		accountNumber(accountNumber), interestRate(interestRate), balance(balance) {}

	int getAccountNumber() const {
		return accountNumber;
	}

	double getInterestRate() const {
		return interestRate;
	}

	double getBalance() const {
		return balance;
	}

	virtual int withdraw(double amount) = 0;
	virtual int deposit(double amount) = 0;
	virtual void display() const = 0;
};

class SavingsAccount : public BankAccount {
public:
	SavingsAccount(int accountNumber, double balance = 0) :
		BankAccount(accountNumber, balance < 10000 ? 1 : 2, balance) {}

	virtual int withdraw(double amount) {
		if (balance >= amount + 2) {
			balance -= amount + 2;
			if (balance < 10000) {
				interestRate = 1;
			}
			return 0;
		}
		else {
			return -1;
		}
	}

	virtual int deposit(double amount) {
		balance += amount;
		if (balance >= 10000) {
			interestRate = 2;
		}
		return 0;
	}

	virtual void display() const {
		cout << "SavingsAccount: "
			<< "accountNumber=" << accountNumber << ", "
			<< "interestRate=" << fixed << setprecision(2) << interestRate << "%, "
			<< "balance=$" << fixed << setprecision(2) << balance << endl;
	}
};

class CheckingAccount : public BankAccount {
protected:
	int numberOfChecks;

public:
	CheckingAccount(int accountNumber, double balance = 0) :
		BankAccount(accountNumber, 0, balance), numberOfChecks(0) {}

	virtual int withdraw(double amount) {
		if (balance >= amount + 5) {
			balance -= amount;
			if (balance < 500) {
				balance -= 5;
			}
			return 0;
		}
		else {
			return -1;
		}
	}

	virtual int deposit(double amount) {
		balance += amount;
		return 0;
	}

	virtual void display() const {
		cout << "CheckingAccount: "
			<< "accountNumber=" << accountNumber << ", "
			<< "interestRate=" << fixed << setprecision(2) << interestRate << "%, "
			<< "balance=$" << fixed << setprecision(2) << balance << ", "
			<< "numberOfChecks=" << numberOfChecks << endl;
	}

	virtual int orderCheck() {
		int result = withdraw(15);
		if (!result) {
			numberOfChecks++;
			return 0;
		}
		else {
			return -1;
		}
	}
};

class CDAccount : public BankAccount {
protected:
	int term;

public:
	CDAccount(int accountNumber, int term, double balance = 0) :
		BankAccount(accountNumber, term >= 5 ? 10 : 5, balance), term(term) {}

	virtual int withdraw(double amount) {
		double fee = balance / 10;
		if (balance >= amount + fee) {
			balance -= amount + fee;
			return 0;
		}
		else {
			return -1;
		}
	}

	virtual int deposit(double amount) {
		balance += amount;
		return 0;
	}

	virtual void display() const {
		cout << "CDAccount: "
			<< "accountNumber=" << accountNumber << ", "
			<< "interestRate=" << fixed << setprecision(2) << interestRate << "%, "
			<< "balance=$" << fixed << setprecision(2) << balance << ", "
			<< "term=" << term << endl;
	}
};

int main() {

	string anykey = " ";

	//Requirments listed in order of appearance within assignment
	// 1. Create a new savings account and deposit $10,000.00
	SavingsAccount savings(1);
	savings.deposit(10000);

	// 2. Create a new checking account and deposit $600.00
	CheckingAccount checking(2);
	checking.deposit(600);

	// 3. Create a new CD account with a 3 year term and deposit $10,000.00
	CDAccount cd(3, 3);
	cd.deposit(10000);

	// 4. Get and display the attributes for each account
	savings.display();
	checking.display();
	cd.display();

	// 5. Calculate monthly interest for the savings account
	double savingsMonthlyInterest = (savings.getInterestRate() / 12) * savings.getBalance();
	cout << fixed << setprecision(2) << "$" << savingsMonthlyInterest << endl;

	// 6. Calculate the monthly interest for the CD account
	double cdMonthlyInterest = (cd.getInterestRate() / 12) * cd.getBalance();
	cout << fixed << setprecision(2) << "$" << cdMonthlyInterest << endl;

	// 7. Get and display the attributes for each account
	savings.display();
	checking.display();
	cd.display();

	// 8. Order checks
	checking.orderCheck();
	checking.orderCheck();
	checking.orderCheck();

	// 9. Withdraw $200.00 from checking
	checking.withdraw(200);

	// 10. Withdraw $1000.00 from savings
	savings.withdraw(1000);

	// 11. Perform an early withdrawal of $2000.00 from the CD account
	cd.withdraw(2000);

	// 12. Get and display the account attributes for each account
	savings.display();
	checking.display();
	cd.display();

	cin >> anykey;
	return 0;
}
