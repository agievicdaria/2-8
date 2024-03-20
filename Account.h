#pragma once
#include <string>
#include <iostream>
using namespace std;

class Account {
public:
    class Money {
    private:
        long hryvnia;
        unsigned char kopiyky;
        static int innerCount;

    public:
        Money();
        Money(long hryvnia, unsigned char kopiyky);
        Money(const Money& second);

        long GetHryvnia() const { return hryvnia; }
        unsigned char GetKopiyky() const { return kopiyky; }
        void SetHryvnia(long value) { hryvnia = value; }
        void SetKopiyky(unsigned char value) { kopiyky = value; }
        static int getInnerCount() { return innerCount; }

        friend Money operator+(const Money& firstValue, const Money& secondValue);
        friend Money operator-(const Money& firstValue, const Money& secondValue);
        friend Money operator/(const Money& value, int divisor);
        friend Money operator/(const Money& value, double divisor);
        friend Money operator*(const Money& value, double multiplier);
        friend bool operator==(const Money& firstValue, const Money& secondValue);
        friend bool operator<(const Money& firstValue, const Money& secondValue);
        friend bool operator>(const Money& firstValue, const Money& secondValue);

        Money& operator=(const Money& other);
        Money& operator++();
        Money operator++(int);
        Money& operator--();
        Money operator--(int);

        friend istream& operator>>(istream& in, Money& money);
        friend ostream& operator<<(ostream& out, const Money& money);
    };

private:
    string ownerLastName;
    int accountNumber;
    double interestRate;
    Money balance;
    static int count;

public:
    Account();
    Account(const string& ownerLastName, int accountNumber, double interestRate, const Money& balance);
    Account(const Account& second);

    const string& GetOwnerLastName() const { return ownerLastName; }
    int GetAccountNumber() const { return accountNumber; }
    double GetInterestRate() const { return interestRate; }
    const Money& GetBalance() const { return balance; }
    void SetOwnerLastName(const string& value) { ownerLastName = value; }
    void SetAccountNumber(int value) { accountNumber = value; }
    void SetInterestRate(double value) { interestRate = value; }
    void SetBalance(const Money& value) { balance = value; }
    static int getCount() { return count; }

    void Withdraw(const Money& amount);
    void Deposit(const Money& amount);
    void AddInterest();
    void ChangeOwner(const string& newOwnerLastName);
    void ConvertToDollars();
    void ConvertToEuros();
    void ConvertToHryvnya();
    string AmountInWords() const;
    operator string() const;


    Account& operator++();
    Account operator++(int);
    Account& operator--();
    Account operator--(int);
    Account& operator=(const Account& other);
    
    friend istream& operator>>(istream& in, Account& account);
    friend ostream& operator<<(ostream& out, const Account& account);
};
