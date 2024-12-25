#include "class.hpp"

Date::Date()
{
     day = month = year = 0;
}

istream& operator>>(istream& i, Date& d)
{
    cout<<"Enter day: ";
    i>>d.day;
    cout<<"Enter month: ";
    i>>d.month;
    cout<<"Enter year: ";
    i>>d.year;
    if(d.isValid())
        return i;
    else
    {
        cout<<"Enter valid date\n";
        i>>d;
        return i;
    }
}

ostream& operator<<(ostream& o, Date d)
{
    o<<d.day<<"-"<<d.month<<"-"<<d.year;
    return o;
}

ifstream& operator>>(ifstream& i, Date& d)
{
    i>>d.day>>d.month>>d.year;
    return i;
}

ofstream& operator<<(ofstream& o, Date d)
{
    o<<d.day<<endl<<d.month<<endl<<d.year;
    return o;
}

int Date::ageCalculate(Date d)
{
    int age = year - d.year;
    if(month < d.month || (month == d.month && day < d.day))
    {
        age--;
    }
    return age;
}

bool Date::isValid()
{
    if(year < 1900 || year > 2023)
        return false;
    if(month < 1 || month > 12)
        return false;
    if (day < 1 || day > daysInMonth())
        return false;
    return true;
}

void Date::setDate()
{
    time_t ist = time(0);
    tm* IST = localtime(&ist);

    day = IST->tm_mday;
    month = IST->tm_mon + 1;
    year = IST->tm_year + 1900;
}

string Date::getDate()
{
    string st = "";
    st = st + to_string(day) + "-";
    st = st + to_string(month) + "-";
    st = st + to_string(year);
    return st;
}

int Date::daysInMonth()
{
    switch(month)
    {
        case 2:
            if(isLeapYear())
                return 29;
            else
                return 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

bool Date::isLeapYear()
{
    if(year % 4 != 0)
        return false;
    else if(year % 100 != 0)
        return true;
    else if(year % 400 != 0)
        return false;
    else
        return true;
}

Time::Time()
{
    hour = minute = second = 0;
}

ostream& operator<<(ostream& o, Time t)
{
    o<<t.hour<<":"<<t.minute<<":"<<t.second;
    return o;
}

ifstream& operator>>(ifstream& i, Time& t)
{
    i>>t.hour>>t.minute>>t.second;
    return i;
}

ofstream& operator<<(ofstream& o, Time t)
{
    o<<t.hour<<endl<<t.minute<<endl<<t.second;
    return o;
}

void Time::setTime()
{
    time_t ist = time(0);
    tm* IST = localtime(&ist);

    hour = IST->tm_hour;
    minute = IST->tm_min;
    second = IST->tm_sec;
}

string Time::getTime()
{
    string st = "";
    st = st + to_string(hour) + ":";
    st = st + to_string(minute) + ":";
    st = st + to_string(second);
    return st;
}

Person::Person()
{
    name[0] = '\0';
    address[0] = '\0';
    phone = aadhaar = 0;
}

istream& operator>>(istream& i, Person& p)
{
    cout<<"Enter name: ";
    i.getline(p.name,20);
    do
    {
        cout<<"Enter gender [M/F/T]: ";
        i>>p.gender;
        p.gender = toupper(p.gender);
        if(p.gender != 'M' && p.gender != 'F' && p.gender != 'T')
            cout<<"Enter a valid gender\n";
    }
    while(p.gender != 'M' && p.gender != 'F' && p.gender != 'T');
    cout<<"Enter date of birth\n";
    i>>p.dob;
    cout<<"Enter address: ";
    i.ignore();
    i.getline(p.address,100);
    do
    {
        cout<<"Enter 10-digit phone number: ";
        i>>p.phone;
        if(to_string(p.phone).length() != 10)
        {
            cout<<"Invalid phone number\n";
        }
    }
    while(to_string(p.phone).length() != 10);
    do
    {
        cout<<"Enter 12-digit Aadhaar number: ";
        i>>p.aadhaar;
        if(to_string(p.aadhaar).length() != 12)
        {
            cout<<"Invalid aadhaar number\n";
        }
    }
    while(to_string(p.aadhaar).length() != 12);
    return i;
}

ostream& operator<<(ostream& o, Person p)
{
    o<<"Name: "<<p.name<<endl;
    o<<"Gender: "<<p.gender<<endl;
    o<<"Date of birth: "<<p.dob<<endl;
    o<<"Address: "<<p.address<<endl;
    o<<"Phone number: "<<p.phone<<endl;
    o<<"Aadhaar number: "<<p.aadhaar<<endl;
    return o;
}

Customer::Customer()
{
    customerId[0] = '\0';
    password[0] = '\0';
}

istream& operator>>(istream& i, Customer& c)
{
    Person* ptr = &c;
    i>>*ptr;
    i.ignore();
    if(strcmp(c.getPassword(),"") == 0)
    {
        cout<<"Enter Customer ID: ";
        i.getline(c.customerId,20);
    }
    do
    {
        cout<<"Set a valid password for Customer: ";
        i.getline(c.password,20);
        if(!c.isValidPassword())
        {
            cout<<"Password must contain atleast 8 characters\n";
        }
    }
    while(!c.isValidPassword());
    return i;
}

ostream& operator<<(ostream& o, Customer c)
{
    Person* ptr = &c;
    o<<*ptr;
    o<<"Customer ID: "<<c.customerId<<endl;
    return o;
}

void Customer::operator=(Customer c)
{
    memcpy(this->name,c.name,20);
    this->gender = c.gender;
    this->dob = c.dob;
    memcpy(this->address,c.address,100);
    this->phone = c.phone;
    this->aadhaar = c.aadhaar;
    memcpy(this->customerId,c.customerId,20);
    memcpy(this->password,c.password,20);
}

bool Customer::isValidPassword()
{
    if(strlen(password) >= 8)
        return true;
    else
        return false;
}

char* Customer::getName()
{
    return name;
}

char Customer::getGender()
{
    return gender;
}

Date Customer::getDOB()
{
    return dob;
}

char* Customer::getAddress()
{
    return address;
}

long long int Customer::getPhone()
{
    return phone;
}

long long int Customer::getAadhaar()
{
    return aadhaar;
}

char* Customer::getId()
{
    return customerId;
}

char* Customer::getPassword()
{
    return password;
}

float Account::rate;

double Account::total;

Account::Account(long long int an): accountNo(an)
{
    pin = 0;
    balance = 0.0;
    status = false;
}

istream& operator>>(istream& i, Account& a)
{
    do
    {
        cout<<"Enter pin: ";
        i>>a.pin;
        if(to_string(a.pin).length() < 4)
        {
            cout<<"Pin should contain atleast 4 digits\n";
        }
    }
    while(to_string(a.pin).length() < 4);
    do
    {
        cout<<"Enter initial balance: ";
        i>>a.balance;
        if(a.balance < 0)
        {
            cout<<"Enter valid initial balance\n";
        }
    }
    while(a.balance < 0);
    cout<<"Enter account status [Active(1)/Inactive(0)]: ";
    i>>a.status;
    return i;
}

ostream& operator<<(ostream& o, Account a)
{
    o<<"Account number: "<<a.accountNo<<endl;
    // o<<"Pin: "<<a.pin<<endl;
    o<<"Balance: "<<a.balance<<endl;
    o<<"Account status: ";
    if(a.status)
        o<<"Active"<<endl;
    else
        o<<"Inactive"<<endl;
    o<<"Account Holder's name: "<<a.c.getName()<<endl;
    o<<"Account Holder's Customer ID : "<<a.c.getId()<<endl;
    return o;
}

double Account::addInterest()
{
    double interest = this->balance * rate / 100;
    this->balance = this->balance + interest;
    return interest;
}

void Account::setCustomer(Customer c)
{
    this->c = c;
}

Customer Account::getCustomer()
{
    return c;
}

long long int Account::getAccountNumber()
{
    return accountNo;
}

int Account::getPin()
{
    return pin;
}

double Account::getBalance()
{
    return balance;
}

bool Account::getStatus()
{
    return status;
}

void Account::deposit()
{
    Transaction tr;
    tr.type = 'D';
    do
    {
        cout<<"Enter the amount you want to deposit: ";
        cin>>tr.amount;
        if(tr.amount <= 0)
        {
            cout<<"Enter valid amount\n";
        }
    }
    while(tr.amount <= 0);
    balance += tr.amount;
    tr.d.setDate();
    tr.t.setTime();
    tr.to = *this;
    tr.writeTransactionToFile();
}

void Account::withdraw()
{
    Transaction tr;
    tr.type = 'W';
    do
    {
        cout<<"Enter the amount you want to withdraw: ";
        cin>>tr.amount;
        if(tr.amount > balance)
        {
            cout<<"You cannot withdraw an amount greater than your balance\n";
        }
        if(tr.amount < 0)
        {
            cout<<"Enter valid amount\n";
        }
    }
    while(tr.amount > balance || tr.amount < 0);
    balance -= tr.amount;
    tr.d.setDate();
    tr.t.setTime();
    tr.from = *this;
    tr.writeTransactionToFile();
}

void Account::transfer(Account& receive)
{
    Transaction tr;
    tr.type = 'T';
    do
    {
        cout<<"Enter the amount you want to transfer: ";
        cin>>tr.amount;
        if(tr.amount > balance)
        {
            cout<<"You cannot transfer an amount greater than your balance\n";
        }
        if(tr.amount < 0)
        {
            cout<<"Enter valid amount\n";
        }
    }
    while(tr.amount > balance || tr.amount < 0);
    balance -= tr.amount;
    receive.balance += tr.amount;
    tr.d.setDate();
    tr.t.setTime();
    tr.from = *this;
    tr.to = receive;
    tr.writeTransactionToFile();
}

void Account::totalValue()
{
    total = total + this->balance;
}

float Account::serviceFee(float fee)
{
    this->balance = this->balance - fee;
    if(balance < 0.0)
    {
        fee = fee + this->balance;
        this->balance = 0.0;
        return fee;
    }
    else
    {
        return fee;
    }
}

float& Account::getRate()
{
    return rate;
}

double& Account::getTotal()
{
    return total;
}

void Account::updateAccount(Customer c)
{
    Account a;
    ifstream fin;
    fin.open("accounts.bin", ios::in|ios::binary);
    fin.seekg(0, ios::beg);
    ofstream fout;
    fout.open("newaccounts.bin", ios::out|ios::binary);
    if(fin.fail() || fout.fail())
    {
        cout<<"File opening unsuccessful\n";
        return;
    }
    while(fin.read((char*)&a,sizeof(a)))
    {
        if(strcmp(a.getCustomer().getId(),c.getId()) == 0)
        {
            a.c = c;
        }
        fout.write((char*)&a,sizeof(a));
    }
    fin.close();
    fout.close();
    remove("accounts.bin");
    rename("newaccounts.bin","accounts.bin");
}

void Account::deleteAccount(Customer c)
{
    Account a;
    ifstream fin;
    fin.open("accounts.bin", ios::in|ios::binary);
    fin.seekg(0, ios::beg);
    ofstream fout;
    fout.open("newaccounts.bin", ios::out|ios::binary);
    if(fin.fail() || fout.fail())
    {
        cout<<"File opening unsuccessful\n";
        return;
    }
    while(fin.read((char*)&a,sizeof(a)))
    {
        if(strcmp(a.getCustomer().getId(),c.getId()) == 0)
        {
            cout<<"______________________________\n";
            cout<<"Details of Account to be deleted\n";
            cout<<a;
            cout<<"______________________________\n";
            cout<<"\nACCOUNT DELETED\n";
            continue;
        }
        fout.write((char*)&a,sizeof(a));
    }
    fin.close();
    fout.close();
    remove("accounts.bin");
    rename("newaccounts.bin","accounts.bin");
}

double Transaction::value;

Transaction::Transaction()
{
    transactId = time(0);
    amount = 0.0;
}

ostream& operator<<(ostream& o, Transaction t)
{
    o<<"Transaction ID: "<<t.transactId<<endl;
    o<<"Amount: "<<t.amount<<endl;
    o<<"Type: ";
    if(t.type == 'D')
    {
        o<<"DEPOSIT"<<endl;
        o<<"Details of account, at the end of the transaction\n";
        o<<"***************\n";
        o<<t.to;
        o<<"***************\n";
        o<<"Date"<<endl<<t.d<<endl;
        o<<"Time"<<endl<<t.t<<endl;
    }
    else if(t.type == 'W')
    {
        o<<"WITHDRAWAL"<<endl;
        o<<"Details of account, at the end of the transaction\n";
        o<<"***************\n";
        o<<t.from;
        o<<"***************\n";
        o<<"Date"<<endl<<t.d<<endl;
        o<<"Time"<<endl<<t.t<<endl;
    }
    else if(t.type == 'T')
    {
        o<<"TRANSFER"<<endl;
        o<<"Details of sender account, at the end of the transaction\n";
        o<<"***************\n";
        o<<t.from;
        o<<"***************\n";
        o<<"Details of receiver account, at the end of the transaction\n";
        o<<"***************\n";
        o<<t.to;
        o<<"***************\n";
        o<<"Date"<<endl<<t.d<<endl;
        o<<"Time"<<endl<<t.t<<endl;
    }
    return o;
}

void Transaction::writeTransactionToFile()
{
    ofstream fout;
    fout.open("transactions.bin", ios::app|ios::binary);
    if(fout.fail())
    {
        cout<<"File opening unsuccessful\n";
        return;
    }
    fout.write((char*)this,sizeof(*this));
    fout.close();
}

int Transaction::getTransactId()
{
    return transactId;
}

double Transaction::getAmount()
{
    return amount;
}

char Transaction::getType()
{
    return type;
}

Date Transaction::getDATE()
{
    return d;
}

Time Transaction::getTIME()
{
    return t;
}

Account Transaction::getFromAccount()
{
    return from;
}

Account Transaction::getToAccount()
{
    return to;
}

void Transaction::totalValue()
{
    value = value + this->amount;
}

double& Transaction::getValue()
{
    return value;
}
