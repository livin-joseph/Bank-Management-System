#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <conio.h>

using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, Date);
    friend ifstream& operator>>(ifstream&, Date&);
    friend ofstream& operator<<(ofstream&, Date);
    int ageCalculate(Date);
    bool isValid();
    void setDate();
    string getDate();

private:
    int daysInMonth();
    bool isLeapYear();
};

class Time
{
private:
    int hour;
    int minute;
    int second;

public:
    Time();
    friend ostream& operator<<(ostream&, Time);
    friend ifstream& operator>>(ifstream&, Time&);
    friend ofstream& operator<<(ofstream&, Time);
    void setTime();
    string getTime();
};

class Person
{
protected:
    char name[20];
    char gender;
    Date dob;
    char address[100];
    long long int phone;
    long long int aadhaar;

public:
    Person();
    friend istream& operator>>(istream&, Person&);
    friend ostream& operator<<(ostream&, Person);
};

class Customer: public Person
{
private:
    char customerId[20];
    char password[20];

public:
    Customer();
    friend istream& operator>>(istream&, Customer&);
    friend ostream& operator<<(ostream&, Customer);
    void operator=(Customer);
    bool isValidPassword();
    char* getName();
    char getGender();
    Date getDOB();
    char* getAddress();
    long long int getPhone();
    long long int getAadhaar();
    char* getId();
    char* getPassword();
};

class Account
{
private:
    long long int accountNo;
    int pin;
    double balance;
    bool status;
    Customer c;
    static float rate;
    static double total;

public:
    Account(long long int an = 0);
    friend istream& operator>>(istream&, Account&);
    friend ostream& operator<<(ostream&, Account);
    double addInterest();
    void setCustomer(Customer);
    Customer getCustomer();
    long long int getAccountNumber();
    int getPin();
    double getBalance();
    bool getStatus();
    void deposit();
    void withdraw();
    void transfer(Account&);
    Account getAccount(long long int);
    void totalValue();
    float serviceFee(float);
    static float& getRate();
    static double& getTotal();
    static void updateAccount(Customer);
    static void deleteAccount(Customer);
};

class Transaction
{
private:
    int transactId;
    double amount;
    char type;
    Date d;
    Time t;
    Account from;
    Account to;
    static double value;

public:
    Transaction();
    friend ostream& operator<<(ostream&, Transaction);
    friend void Account::deposit();
    friend void Account::withdraw();
    friend void Account::transfer(Account&);
    void writeTransactionToFile();
    int getTransactId();
    double getAmount();
    char getType();
    Date getDATE();
    Time getTIME();
    Account getFromAccount();
    Account getToAccount();
    void totalValue();
    static double& getValue();
};

#endif
