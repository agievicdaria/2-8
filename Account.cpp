#include "Account.h"
#include <string>
#include <sstream> 
#include <iostream>
using namespace std;

int Account::count = 0;
int Account::Money::innerCount = 0;

Account::Money::Money() {
    hryvnia = 0;
    kopiyky = 0;
    Account::Money::innerCount++;
}

Account::Money::Money(long hryvnia, unsigned char kopiyky) {
    this->hryvnia = hryvnia;
    this->kopiyky = kopiyky;
    Account::Money::innerCount++;
}

Account::Money::Money(const Money& second) {
    hryvnia = second.hryvnia;
    kopiyky = second.kopiyky;
    Account::Money::innerCount++;
}

Account::Money& Account::Money::operator=(const Money& other) {
    if (this == &other)
        return *this;

    hryvnia = other.hryvnia;
    kopiyky = other.kopiyky;

    return *this;
}

istream& operator>>(istream& in, Account::Money& money) {
    cout << "Enter amount in hryvnia: ";
    in >> money.hryvnia;

    cout << "Enter amount in kopiyky: ";
    in >> money.kopiyky;

    return in;
}

ostream& operator<<(ostream& out, const Account::Money& money) {
    out << money.hryvnia << " hryvnia " << static_cast<int>(money.kopiyky) << " kopiyok";
    return out;
}

Account::Money operator+(const Account::Money& firstValue, const Account::Money& secondValue) {
    long totalHryvnia = firstValue.hryvnia + secondValue.hryvnia;
    int totalKopiyky = firstValue.kopiyky + secondValue.kopiyky;

    if (totalKopiyky >= 100) {
        totalHryvnia += totalKopiyky / 100;
        totalKopiyky %= 100;
    }

    return Account::Money(totalHryvnia, static_cast<unsigned char>(totalKopiyky));
}

Account::Money operator-(const Account::Money& firstValue, const Account::Money& secondValue) {
    long totalHryvnia = firstValue.hryvnia - secondValue.hryvnia;
    int totalKopiyky = firstValue.kopiyky - secondValue.kopiyky;

    if (totalKopiyky < 0) {
        totalHryvnia -= 1;
        totalKopiyky += 100;
    }

    return Account::Money(totalHryvnia, static_cast<unsigned char>(totalKopiyky));
}

Account::Money operator/(const Account::Money& value, int divisor) {
    long totalHryvnia = value.hryvnia / divisor;
    int totalKopiyky = (value.hryvnia % divisor) * 100 / divisor + value.kopiyky / divisor;

    return Account::Money(totalHryvnia, static_cast<unsigned char>(totalKopiyky));
}

Account::Money operator/(const Account::Money& value, double divisor) {
    double totalMoney = static_cast<double>(value.hryvnia * 100 + value.kopiyky) / divisor;
    long totalHryvnia = static_cast<long>(totalMoney) / 100;
    int totalKopiyky = static_cast<int>(totalMoney) % 100;

    return Account::Money(totalHryvnia, static_cast<unsigned char>(totalKopiyky));
}

Account::Money operator*(const Account::Money& value, double multiplier) {
    double totalMoney = static_cast<double>(value.hryvnia * 100 + value.kopiyky) * multiplier;
    long totalHryvnia = static_cast<long>(totalMoney) / 100;
    int totalKopiyky = static_cast<int>(totalMoney) % 100;

    return Account::Money(totalHryvnia, static_cast<unsigned char>(totalKopiyky));
}

bool operator==(const Account::Money& firstValue, const Account::Money& secondValue) {
    return firstValue.hryvnia == secondValue.hryvnia && firstValue.kopiyky == secondValue.kopiyky;
}

bool operator<(const Account::Money& firstValue, const Account::Money& secondValue) {
    if (firstValue.hryvnia == secondValue.hryvnia) {
        return firstValue.kopiyky < secondValue.kopiyky;
    }
    return firstValue.hryvnia < secondValue.hryvnia;
}

bool operator>(const Account::Money& firstValue, const Account::Money& secondValue) {
    if (firstValue.hryvnia == secondValue.hryvnia) {
        return firstValue.kopiyky > secondValue.kopiyky;
    }
    return firstValue.hryvnia > secondValue.hryvnia;
}

Account::Money& Account::Money::operator++() {
    ++hryvnia;
    return *this;
}

Account::Money Account::Money::operator++(int) {
    Money m(*this);
    ++kopiyky;
    if (kopiyky == 100) {
        ++hryvnia;
        kopiyky = 0;
    }
    return m;
}

Account::Money& Account::Money::operator--() {
    --hryvnia;
    return *this;
}

Account::Money Account::Money::operator--(int) {
    Money m(*this);
    if (kopiyky == 0) {
        --hryvnia;
        kopiyky = 99;
    } else {
        --kopiyky;
    }
    return m;
}

Account::Account() {
    ownerLastName = "";
    accountNumber = 0;
    interestRate = 0.0;
    balance = Money();
    count++;
}

Account::Account(const string& ownerLastName, int accountNumber, double interestRate, const Money& balance) {
    this->ownerLastName = ownerLastName;
    this->accountNumber = accountNumber;
    this->interestRate = interestRate;
    this->balance = balance;
    count++;
}

Account::Account(const Account& second) {
    ownerLastName = second.ownerLastName;
    accountNumber = second.accountNumber;
    interestRate = second.interestRate;
    balance = second.balance;
    count++;
}

Account& Account::operator=(const Account& other) {
    if (this == &other)
        return *this;

    ownerLastName = other.ownerLastName;
    accountNumber = other.accountNumber;
    interestRate = other.interestRate;
    balance = other.balance;

    return *this;
}

istream& operator>>(istream& in, Account& account) {
    cout << "Enter owner's last name: ";
    in >> account.ownerLastName;

    cout << "Enter account number: ";
    in >> account.accountNumber;

    cout << "Enter interest rate: ";
    in >> account.interestRate;

    cout << "Enter balance (in hryvnia and kopiyky): ";
    in >> account.balance;

    return in;
}

ostream& operator<<(ostream& out, const Account& account) {
    out << string(account);
    return out;
}

void Account::ChangeOwner(const string& newOwnerLastName) {
    ownerLastName = newOwnerLastName;
}

void Account::ConvertToDollars() {
    double exchangeRate = 0.026;
    balance = balance * exchangeRate;
}

void Account::ConvertToEuros() {
    double exchangeRate = 0.91;
    balance = balance * exchangeRate;
}

void Account::ConvertToHryvnya() {
    double exchangeRate = 42.38;
    balance = balance * exchangeRate;
}

string Account::AmountInWords() const {
    const string _thousands[10] = { "", "tysyacha", "dvi tysiachy", "try tysiachy", "4otyry tysiachy", "p’jat tysiach", "6ist tysiach", "sim tysiach", "visim tysiach", "dev’jat tysiach" };
    const string _centuries[10] = { "", "sto", "dvisti", "trysta", "4onyrysta", "p’jatsot", "6istsot", "simsot", "visimsot", "dev’jatsot" };
    const string _decades[10] = { "", "", "dvadciat’", "trydciat’", "sorok", "p’jatdesiat", "6istdesiat", "simdesiat", "visimdesiat", "dev’janosto" };
    const string _digits[20] = { "", "odyn", "dva", "try", "4otyry", "p’jat’", "6ist’", "sim", "visim", "dev’jat’", "desiat’", "odynadciad’", "dvanadciad’", "trynadciad’", "4otyrnadciad’", "p’jatnadciad’", "6istnadciad’", "simnadciad’", "visimnadciad’", "dev’jatnadciad’" };

    long absBalance = abs(balance.GetHryvnia());
    int thousands = absBalance / 1000;
    absBalance %= 1000;
    int cen = absBalance / 100;
    absBalance %= 100;
    int dec = absBalance / 10;
    int dig = absBalance % 10;

    string amountInWords = "";
    if (thousands > 0)
        amountInWords += _thousands[thousands] + " ";

    amountInWords += _centuries[cen] + " " + _decades[dec] + " " + _digits[dig];

    amountInWords += " hryvnia " + to_string(balance.GetKopiyky()) + " kopiyok";

    return amountInWords;
}

Account::operator string() const {
    stringstream sout;
    sout << "Owner: " << ownerLastName << endl;
    sout << "Account Number: " << accountNumber << endl;
    sout << "Interest Rate: " << interestRate << endl;
    sout << "Balance: " << balance.GetHryvnia() << "," << static_cast<int>(balance.GetKopiyky()) << endl;
    return sout.str();
}

void Account::Withdraw(const Money& amount) {
    if (balance > amount) {
        balance = balance - amount;
        cout << "Withdrawal successful." << endl;
    } else {
        cout << "Insufficient funds." << endl;
    }
}

void Account::Deposit(const Money& amount) {
    balance = balance + amount;
    cout << "Deposit successful." << endl;
}

void Account::AddInterest() {
    Money interest = balance * interestRate;
    balance = balance + interest;
}

Account& Account::operator++() {
    ++accountNumber;
    return *this;
}

Account Account::operator++(int) {
    Account a(*this);
    ++interestRate;
    return a;
}

Account& Account::operator--() {
    --accountNumber;
    return *this;
}

Account Account::operator--(int) {
    Account a(*this);
    --interestRate;
    return a;
}
