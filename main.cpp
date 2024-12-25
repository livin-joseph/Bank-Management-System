#include "class.hpp"
#include "tabulate-master\single_include\tabulate\tabulate.hpp"

using namespace tabulate;

void welcome()
{
    cout<<"++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+        BANK MANAGEMENT SYSTEM        +"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"-              Bhuvanesh D    [22PD07] -"<<endl;
    cout<<"-              Livin Joseph J [22PD20] -"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<endl;
}

void endProgram()
{
    cout<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+    BANK MANAGEMENT SYSTEM (v1.2.0)   +"<<endl;
    cout<<"+                                      +"<<endl;
    cout<<"+              Bhuvanesh D    [22PD07] +"<<endl;
    cout<<"+              Livin Joseph J [22PD20] +"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<endl;
}

void loginCustomer()
{
    char cusId[20];
    char pass[20];
    Customer c;
    bool flag = false;
    cout<<"Enter Customer ID: ";
    cin.ignore();
    cin.getline(cusId,20);
    ifstream fin;
    fin.open("customers.bin", ios::in|ios::binary);
    fin.seekg(0, ios::beg);
    if(fin.fail())
    {
        cout<<"File opening unsuccessful\n";
        return;
    }
    while(fin.read((char*)&c,sizeof(c)))
    {
        if(strcmp(c.getId(),cusId) == 0)
        {
            cout<<"Customer found\n";
            cout<<"______________________________\n";
            cout<<"Enter password: ";
            int i = 0;
            while(true)
            {
                char ch = getch();
                if(ch == 13 || i >= 20)
                    break;
                cout<<"*";
                pass[i] = ch;
                i++;
            }
            pass[i] = '\0';
            if(strcmp(c.getPassword(),pass) == 0)
            {
                cout<<"\nLogin successful\n";
                cout<<"______________________________\n";
                cout<<c;
                cout<<"______________________________\n";
            }
            else
            {
                cout<<"\nIncorrect password\n";
                return;
            }
            flag = true;
        }
        if(flag == true)
            break;
    }
    fin.close();
    if(flag == false)
    {
        cout<<"No Customer found with the entered Customer ID\n";
        return;
    }
    int choice;
    do
    {
        cout<<"\nCUSTOMER MENU\n";
        cout<<" 1] View Customer details\n";
        cout<<" 2] View Customer's benefits and regulations\n";
        cout<<" 3] View Customer's Accounts details\n";
        cout<<" 4] Show Customer's net worth\n";
        cout<<" 5] Perform transaction\n";
        cout<<" 6] Show previous transactions\n";
        cout<<" 0] Logout\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            break;
        case 1:
            cout<<"______________________________\n";
            cout<<c;
            cout<<"______________________________\n";
            break;
        case 2:
        {
            Date today;
            today.setDate();
            cout<<"______________________________\n";
            if(c.getGender() == 'F' && today.ageCalculate(c.getDOB()) < 18)
            {
                cout<<"---> Shakthi benefits for female child\n";
                cout<<"---> All transactions should be done only with parental guidance\n";
            }
            else if(c.getGender() == 'M' && today.ageCalculate(c.getDOB()) < 18)
            {
                cout<<"---> Junior benefits for male child\n";
                cout<<"---> All transactions should be done only with parental guidance\n";
            }
            else if(today.ageCalculate(c.getDOB()) > 60)
                cout<<"---> Senior citizen benefits\n";
            else if(c.getGender() == 'F' && today.ageCalculate(c.getDOB()) > 30)
                cout<<"---> Mahila Shubha benefits for female customers\n";
            else if(today.ageCalculate(c.getDOB()) < 23)
                cout<<"---> Student & youth benefits\n";
            else if(today.ageCalculate(c.getDOB()) < 30)
                cout<<"---> Energetic youth benefits\n";
            else
                cout<<"---> No benefits\n";
            cout<<"______________________________\n";
            break;
        }
        case 3:
        {
            bool flag = false;
            Account a;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&a,sizeof(a)))
            {
                if(strcmp(a.getCustomer().getId(),c.getId()) == 0)
                {
                    cout<<a;
                    cout<<"______________________________\n";
                    flag = true;
                }
            }
            fin.close();
            if(flag == false)
            {
                cout<<"Customer has no account\n";
            }
            break;
        }
        case 4:
        {
            bool flag = false;
            Account a;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            double netWorth = 0.0;
            while(fin.read((char*)&a,sizeof(a)))
            {
                if(strcmp(a.getCustomer().getId(),c.getId()) == 0)
                {
                    netWorth += a.getBalance();
                    flag = true;
                }
            }
            fin.close();
            if(flag == false)
            {
                cout<<"Customer has no account\n";
            }
            else
            {
                cout<<"Customer's net worth: "<<netWorth<<endl;
            }
            break;
        }
        case 5:
        {
            bool flag = false;
            Account a;
            long long int accNo;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&a,sizeof(a)))
            {
                if(strcmp(a.getCustomer().getId(),c.getId()) == 0)
                {
                    if(flag == false)
                    {
                        cout<<"Choose from which account you would like to transact\n";
                        cout<<"Account numbers and their statuses are given below\n";
                    }
                    cout<<a.getAccountNumber()<<" ---> ";
                    (a.getStatus())? cout<<"Active\n" : cout<<"Inactive\n";
                    flag = true;
                }
            }
            if(flag == false)
            {
                cout<<"Customer has no account\n";
                break;
            }
            fin.close();
            cout<<"Enter the account number: ";
            cin>>accNo;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            Account tempor,tempor1;
            cout<<"______________________________\n";
            while(fin.read((char*)&tempor,sizeof(tempor)))
            {
                if(tempor.getAccountNumber() == accNo)
                {
                    if(tempor.getStatus() == false)
                    {
                        cout<<"Account is inactive\n";
                        cout<<"Transaction cannot be performed with inactive account\n";
                        cout<<"Visit bank branch to activate the account\n";
                        flag = false;
                        break;
                    }
                    cout<<"Logging in into Account\n";
                    cout<<tempor;
                    flag = true;
                    break;
                }
            }
            fin.close();
            if(flag == false)
            {
                break;
            }
            if(tempor.getAccountNumber() != accNo)
            {
                cout<<"Invalid account number\n";
                break;
            }
            cout<<"Enter pin: ";
            string password = "";
            while(true)
            {
                char ch = getch();
                if(ch == 13)
                    break;
                cout<<"*";
                password.push_back(ch);
            }
            int loginPin = stoi(password);
            if(loginPin != tempor.getPin())
            {
                cout<<"\nIncorrect pin\n";
                cout<<"Log in failed\n";
                break;
            }
            cout<<"\nLog in successful\n\n";
            char tt;
            do
            {
                cout<<"Enter 'D' to deposit\n";
                cout<<"Enter 'W' to withdraw\n";
                cout<<"Enter 'T' to transfer\n";
                cout<<"Enter the type of transaction you want to perform: ";
                cin>>tt;
                tt = toupper(tt);
                switch(tt)
                {
                case 'D':
                    tempor.deposit();
                    cout<<"DEPOSIT SUCCESSFUL\n";
                    break;
                case 'W':
                    tempor.withdraw();
                    cout<<"WITHDRAWAL SUCCESSFUL\n";
                    break;
                case 'T':
                {
                    cout<<"Enter the account number to which you want to transfer money: ";
                    cin>>accNo;
                    fin.open("accounts.bin", ios::in|ios::binary);
                    fin.seekg(0, ios::beg);
                    flag = false;
                    bool exist = false;
                    cout<<"______________________________\n";
                    while(fin.read((char*)&tempor1,sizeof(tempor1)))
                    {
                        if(tempor1.getAccountNumber() == accNo)
                        {
                            exist = true;
                            if(tempor1.getStatus() == false)
                            {
                                cout<<"Account is inactive\n";
                                cout<<"Transfer cannot be performed to inactive account\n";
                                break;
                            }
                            cout<<tempor1;
                            cout<<"______________________________\n";
                            flag = true;
                            break;
                        }
                    }
                    fin.close();
                    if(exist == false)
                    {
                        cout<<"Transaction failed: Account does not exist\n";
                        break;
                    }
                    if(flag == false)
                    {
                        cout<<"Transaction failed: Account is inactive\n";
                        break;
                    }
                    tempor.transfer(tempor1);
                    cout<<"TRANSACTION SUCCESSFUL\n";
                    break;
                }
                default:
                    cout<<"Invalid choice\n";
                }
            }
            while(tt != 'D' && tt != 'W' && tt != 'T');

            //Modify accounts.bin file
            Account tempo;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            ofstream fout;
            fout.open("newaccounts.bin", ios::out|ios::binary);
            if(fin.fail() || fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&tempo,sizeof(tempo)))
            {
                if(tempor.getAccountNumber() == tempo.getAccountNumber())
                {
                    fout.write((char*)&tempor,sizeof(tempor));
                    continue;
                }
                if(tt == 'T' && tempor1.getAccountNumber() == tempo.getAccountNumber())
                {
                    fout.write((char*)&tempor1,sizeof(tempor1));
                    continue;
                }
                fout.write((char*)&tempo,sizeof(tempo));
            }
            fin.close();
            fout.close();
            remove("accounts.bin");
            rename("newaccounts.bin","accounts.bin");
            break;
        }
        case 6:
        {
            bool flag = false;
            Account a1,a2;
            Transaction tr;
            ifstream fin;
            fin.open("transactions.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            Table t;
            t.add_row({"Transaction ID","Amount","Type","Date","Time","From Account","To Account"});
            while(fin.read((char*)&tr,sizeof(tr)))
            {
                a1 = tr.getFromAccount();
                a2 = tr.getToAccount();
                if(strcmp(a1.getCustomer().getId(),c.getId()) == 0 || strcmp(a2.getCustomer().getId(),c.getId()) == 0)
                {
                    string t1 = to_string(tr.getTransactId());
                    string t2 = to_string(tr.getAmount());
                    char ch = tr.getType();
                    string t3 = (ch == 'T')? "Transfer" : (ch == 'D')? "Deposit" : "Withdrawal";
                    string t4 = tr.getDATE().getDate();
                    string t5 = tr.getTIME().getTime();
                    Account check = tr.getFromAccount();
                    string t6 = to_string(check.getAccountNumber());
                    check = tr.getToAccount();
                    string t7 = to_string(check.getAccountNumber());
                    if(t6 == "0")
                        t6 = "";
                    if(t7 == "0")
                        t7 = "";
                    t.add_row({t1,t2,t3,t4,t5,t6,t7});
                    flag = true;
                }
            }
            fin.close();
            if(flag == false)
            {
                cout<<"Customer has no transaction\n";
            }
            else
            {
                cout<<"Customer's previous transactions\n"<<t<<endl;
            }
            cout<<"______________________________\n";
            break;
        }
        default:
            cout<<"Invalid choice\n";
        }
    }
    while(choice != 0);
}

void loginAdmin()
{
    char ch;
    string password = "";
    string realpass = "1234";
    cout<<"Enter password: ";
    while(true)
    {
        ch = getch();
        if(ch == 13)
            break;
        cout<<"*";
        password.push_back(ch);
    }
    if(password != realpass)
    {
        cout<<"\nIncorrect password\n";
        return;
    }
    cout<<endl;
    int choice;
    do
    {
        cout<<"\nADMINISTRATOR MENU\n";
        cout<<" 1] Create new Customer\n";
        cout<<" 2] Search Customer\n";
        cout<<" 3] Modify Customer details\n";
        cout<<" 4] Delete Customer\n";
        cout<<" 5] Create new Account\n";
        cout<<" 6] Search Account\n";
        cout<<" 7] Modify Account details\n";
        cout<<" 8] Delete Account\n";
        cout<<" 9] Add Monthly Interest to all Accounts\n";
        cout<<"10] Collect Service Fee from all Accounts\n";
        cout<<"11] Search Transaction\n";
        cout<<"12] Display all Customers\n";
        cout<<"13] Display all Accounts\n";
        cout<<"14] Display all Transactions\n";
        cout<<" 0] Logout\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            break;
        case 1:
        {
            cout<<"\nNEW CUSTOMER\n";
            Customer c;
            cin.ignore();
            cin>>c;
            ofstream fout;
            fout.open("customers.bin", ios::app|ios::binary);
            if(fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            fout.write((char*)&c,sizeof(c));
            fout.close();
            cout<<"\nNEW CUSTOMER CREATED\n";
            break;
        }
        case 2:
        {
            cout<<"\nSEARCH CUSTOMER\n";
            Customer c;
            char cusId[20];
            bool flag = false;
            cout<<"Enter Customer ID: ";
            cin.ignore();
            cin.getline(cusId,20);
            ifstream fin;
            fin.open("customers.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&c,sizeof(c)))
            {
                if(strcmp(c.getId(),cusId) == 0)
                {
                    cout<<"Details of Customer\n";
                    cout<<c;
                    cout<<"______________________________\n";
                    flag = true;
                }
            }
            fin.close();
            if(flag == false)
            {
                cout<<"No Customer found with the entered Customer ID\n";
            }
            break;
        }
        case 3:
        {
            cout<<"\nMODIFY CUSTOMER DETAILS\n";
            Customer c,temp;
            char cusId[20];
            bool flag = false;
            cout<<"Enter Customer ID: ";
            cin.ignore();
            cin.getline(cusId,20);
            ifstream fin;
            fin.open("customers.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            ofstream fout;
            fout.open("newcustomers.bin", ios::out|ios::binary);
            if(fin.fail() || fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&c,sizeof(c)))
            {
                if(strcmp(c.getId(),cusId) == 0)
                {
                    cout<<"Present Details of Customer\n";
                    cout<<c;
                    cout<<"______________________________\n";
                    cout<<"Enter Modified Details of Customer\n";
                    cin>>c;
                    temp = c;
                    cout<<"\nCUSTOMER DETAILS MODIFIED\n";
                    cout<<"______________________________\n";
                    flag = true;
                }
                fout.write((char*)&c,sizeof(c));
            }
            fin.close();
            fout.close();
            remove("customers.bin");
            rename("newcustomers.bin","customers.bin");
            if(flag == false)
            {
                cout<<"No Customer found with the entered Customer ID\n";
            }
            else
            {
                cout<<"Updating accounts of the Customer\n";
                Account::updateAccount(temp);
                cout<<"\nUPDATION SUCCESSFUL\n";
            }
            break;
        }
        case 4:
        {
            cout<<"\nDELETE CUSTOMER\n";
            Customer c,temp;
            char cusId[20];
            bool flag = false;
            cout<<"Enter Customer ID: ";
            cin.ignore();
            cin.getline(cusId,20);
            ifstream fin;
            fin.open("customers.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            ofstream fout;
            fout.open("newcustomers.bin", ios::out|ios::binary);
            if(fin.fail() || fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&c,sizeof(c)))
            {
                if(strcmp(c.getId(),cusId) == 0)
                {
                    cout<<"Details of Customer to be deleted\n";
                    cout<<c;
                    temp = c;
                    cout<<"______________________________\n";
                    cout<<"\nCUSTOMER DELETED\n";
                    flag = true;
                    continue;
                }
                fout.write((char*)&c,sizeof(c));
            }
            fin.close();
            fout.close();
            remove("customers.bin");
            rename("newcustomers.bin","customers.bin");
            if(flag == false)
            {
                cout<<"No Customer found with the entered Customer ID\n";
            }
            else
            {
                Account::deleteAccount(temp);
            }
            break;
        }
        case 5:
        {
            cout<<"\nNEW ACCOUNT\n";
            Customer c;
            char cusId[20];
            bool flag = false;
            cout<<"Enter Customer ID: ";
            cin.ignore();
            cin.getline(cusId,20);
            ifstream fin;
            fin.open("customers.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&c,sizeof(c)))
            {
                if(strcmp(c.getId(),cusId) == 0)
                {
                    cout<<"Customer found\n";
                    cout<<"Customer name: "<<c.getName()<<endl;
                    cout<<"______________________________\n";
                    flag = true;
                    break;
                }
            }
            fin.close();
            if(flag == false)
            {
                cout<<"No Customer found with the entered Customer ID\n";
                break;
            }
            long long int an;
            cout<<"Enter account number: ";
            cin>>an;
            Account a(an);
            cin>>a;
            a.setCustomer(c);
            ofstream fout;
            fout.open("accounts.bin", ios::app|ios::binary);
            if(fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            fout.write((char*)&a,sizeof(a));
            fout.close();
            cout<<"\nNEW ACCOUNT CREATED\n";
            break;
        }
        case 6:
        {
            cout<<"\nSEARCH ACCOUNT\n";
            long long int accNo;
            bool flag = false;
            cout<<"Enter Account No: ";
            cin>>accNo;
            Account a;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&a,sizeof(a)))
            {
                if(a.getAccountNumber() == accNo)
                {
                    cout<<a;
                    cout<<"______________________________\n";
                    flag = true;
                }
            }
            fin.close();
            if(flag == false)
            {
                cout<<"No Account found with the entered Account number\n";
            }
            break;
        }
        case 7:
        {
            cout<<"\nMODIFY ACCOUNT DETAILS\n";
            long long int accNo;
            bool flag = false;
            cout<<"Enter Account No: ";
            cin>>accNo;
            Account a;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            ofstream fout;
            fout.open("newaccounts.bin", ios::out|ios::binary);
            if(fin.fail() || fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&a,sizeof(a)))
            {
                if(a.getAccountNumber() == accNo)
                {
                    cout<<"Present Details of Account\n";
                    cout<<a;
                    cout<<"______________________________\n";
                    cout<<"Enter Modified Details of Account\n";
                    cin>>a;
                    cout<<"\nACCOUNT DETAILS MODIFIED\n";
                    cout<<"______________________________\n";
                    flag = true;
                }
                fout.write((char*)&a,sizeof(a));
            }
            fin.close();
            fout.close();
            remove("accounts.bin");
            rename("newaccounts.bin","accounts.bin");
            if(flag == false)
            {
                cout<<"No Account found with the entered Account number\n";
            }
            break;
        }
        case 8:
        {
            cout<<"\nDELETE ACCOUNT\n";
            long long int accNo;
            bool flag = false;
            cout<<"Enter Account No: ";
            cin>>accNo;
            Account a;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            ofstream fout;
            fout.open("newaccounts.bin", ios::out|ios::binary);
            if(fin.fail() || fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            cout<<"______________________________\n";
            while(fin.read((char*)&a,sizeof(a)))
            {
                if(a.getAccountNumber() == accNo)
                {
                    cout<<"Details of Account to be deleted\n";
                    cout<<a;
                    cout<<"______________________________\n";
                    cout<<"\nACCOUNT DELETED\n";
                    flag = true;
                    continue;
                }
                fout.write((char*)&a,sizeof(a));
            }
            fin.close();
            fout.close();
            remove("accounts.bin");
            rename("newaccounts.bin","accounts.bin");
            if(flag == false)
            {
                cout<<"No Account found with the entered Account number\n";
            }
            break;
        }
        case 9:
        {
            bool flag = false;
            Account a;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            ofstream fout;
            fout.open("newaccounts.bin", ios::out|ios::binary);
            if(fin.fail() || fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            float rt;
            cout<<"Interest is compounded monthly\n";
            do
            {
                cout<<"Enter the rate of interest: ";
                cin>>rt;
                if(rt < 0)
                {
                    cout<<"Invalid rate of interest\n";
                }
            }
            while(rt < 0);
            Account::getRate() = rt;
            cout<<"______________________________\n";
            double amt = 0.0;
            while(fin.read((char*)&a,sizeof(a)))
            {
                flag = true;
                amt = amt + a.addInterest();
                fout.write((char*)&a,sizeof(a));
            }
            fin.close();
            fout.close();
            remove("accounts.bin");
            rename("newaccounts.bin","accounts.bin");
            if(flag == false)
            {
                cout<<"No Account found\n";
            }
            else
            {
                cout<<"\nMONTHLY INTEREST ADDED TO ALL ACCOUNTS\n";
                cout<<"TOTAL INTEREST ADDED: "<<amt<<endl<<endl;
            }
            break;
        }
        case 10:
        {
            bool flag = false;
            Account a;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            fin.seekg(0, ios::beg);
            ofstream fout;
            fout.open("newaccounts.bin", ios::out|ios::binary);
            if(fin.fail() || fout.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            float fee;
            cout<<"Service fee is charged annually\n";
            do
            {
                cout<<"Enter the service fee: ";
                cin>>fee;
                if(fee < 0)
                {
                    cout<<"Invalid rate of interest\n";
                }
            }
            while(fee < 0);
            cout<<"______________________________\n";
            double amt = 0.0;
            while(fin.read((char*)&a,sizeof(a)))
            {
                flag = true;
                amt = amt + a.serviceFee(fee);
                fout.write((char*)&a,sizeof(a));
            }
            fin.close();
            fout.close();
            remove("accounts.bin");
            rename("newaccounts.bin","accounts.bin");
            if(flag == false)
            {
                cout<<"No Account found\n";
            }
            else
            {
                cout<<"\nSERVICE FEE COLLECTED FROM ALL ACCOUNTS\n";
                cout<<"TOTAL SERVICE FEE COLLECTED: "<<amt<<endl<<endl;
            }
            break;
        }
        case 11:
        {
            cout<<"\nSEARCH TRANSACTIONS\n";
            cout<<"______________________________\n";
            Table t;
            t.add_row({"Transaction ID","Amount","Type","Date","Time","From Account","To Account"});
            bool flag = false;
            long long int accNo;
            cout<<"Enter Account Number: ";
            cin>>accNo;
            Transaction d;
            ifstream fin;
            fin.open("transactions.bin", ios::in|ios::binary);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            fin.seekg(0);
            while(fin.read((char*)&d,sizeof(d)))
            {
                if(d.getFromAccount().getAccountNumber() == accNo || d.getToAccount().getAccountNumber() == accNo)
                {
                    cout<<d;
                    string t1 = to_string(d.getTransactId());
                    string t2 = to_string(d.getAmount());
                    char ch = d.getType();
                    string t3 = (ch == 'T')? "Transfer" : (ch == 'D')? "Deposit" : "Withdrawal";
                    string t4 = d.getDATE().getDate();
                    string t5 = d.getTIME().getTime();
                    Account check = d.getFromAccount();
                    string t6 = to_string(check.getAccountNumber());
                    check = d.getToAccount();
                    string t7 = to_string(check.getAccountNumber());
                    if(t6 == "0")
                        t6 = "";
                    if(t7 == "0")
                        t7 = "";
                    t.add_row({t1,t2,t3,t4,t5,t6,t7});
                    flag = true;
                    cout<<"______________________________\n";
                }
            }
            if(flag == false)
            {
                cout<<"No transactions found\n";
            }
            else
            {
                cout<<"\nSUMMARY\n";
                cout<<t<<endl;
                cout<<"______________________________\n";
            }
            fin.close();
            break;
        }
        case 12:
        {
            cout<<"\nALL CUSTOMERS DETAILS\n";
            cout<<"______________________________\n";
            Table t;
            t.add_row({"Customer ID","Name","Gender","Age","Address","Phone number","Aadhaar number"});
            Customer d;
            ifstream fin;
            fin.open("customers.bin", ios::in|ios::binary);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            fin.seekg(0);
            while(fin.read((char*)&d,sizeof(d)))
            {
                string t1 = d.getId();
                string t2 = d.getName();
                string t3 = "";
                t3.push_back(d.getGender());
                string t4 = d.getDOB().getDate();
                string t5 = d.getAddress();
                string t6 = to_string(d.getPhone());
                string t7 = to_string(d.getAadhaar());
                t.add_row({t1,t2,t3,t4,t5,t6,t7});
            }
            cout<<t<<endl;
            cout<<"______________________________\n";
            fin.close();
            break;
        }
        case 13:
        {
            cout<<"\nALL ACCOUNTS DETAILS\n";
            cout<<"______________________________\n";
            Table t;
            t.add_row({"Account number","Customer ID","Account Holder's name","Balance","Account status"});
            Account d;
            Account::getTotal() = 0.0;
            ifstream fin;
            fin.open("accounts.bin", ios::in|ios::binary);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            fin.seekg(0);
            while(fin.read((char*)&d,sizeof(d)))
            {
                string t1 = to_string(d.getAccountNumber());
                string t2 = d.getCustomer().getId();
                string t3 = d.getCustomer().getName();
                string t4 = to_string(d.getBalance());
                string t5 = d.getStatus()? "Active" : "Inactive";
                t.add_row({t1,t2,t3,t4,t5});
                d.totalValue();
            }
            cout<<t<<endl;
            cout<<"______________________________\n";
            cout<<"TOTAL AMOUNT IN ALL ACCOUNTS: "<<Account::getTotal()<<endl<<endl;
            fin.close();
            break;
        }
        case 14:
        {
            cout<<"\nALL TRANSACTIONS DETAILS\n";
            cout<<"______________________________\n";
            Table t;
            t.add_row({"Transaction ID","Amount","Type","Date","Time","From Account","To Account"});
            Transaction d;
            Transaction::getValue() = 0.0;
            ifstream fin;
            fin.open("transactions.bin", ios::in|ios::binary);
            if(fin.fail())
            {
                cout<<"File opening unsuccessful\n";
                break;
            }
            fin.seekg(0);
            while(fin.read((char*)&d,sizeof(d)))
            {
                cout<<d;
                string t1 = to_string(d.getTransactId());
                string t2 = to_string(d.getAmount());
                char ch = d.getType();
                string t3 = (ch == 'T')? "Transfer" : (ch == 'D')? "Deposit" : "Withdrawal";
                string t4 = d.getDATE().getDate();
                string t5 = d.getTIME().getTime();
                Account check = d.getFromAccount();
                string t6 = to_string(check.getAccountNumber());
                check = d.getToAccount();
                string t7 = to_string(check.getAccountNumber());
                if(t6 == "0")
                    t6 = "";
                if(t7 == "0")
                    t7 = "";
                t.add_row({t1,t2,t3,t4,t5,t6,t7});
                d.totalValue();
                cout<<"______________________________\n";
            }
            cout<<"\nSUMMARY\n";
            cout<<t<<endl;
            cout<<"______________________________\n";
            cout<<"TOTAL AMOUNT IN ALL ACCOUNTS: "<<Transaction::getValue()<<endl<<endl;
            fin.close();
            break;
        }
        default:
            cout<<"Invalid choice\n";
        }
    }
    while(choice != 0);
}

int main()
{
    welcome();
    int choice;
    do
    {
        cout<<"\nMAIN MENU\n";
        cout<<"1. Login as Customer\n";
        cout<<"2. Login as Administrator\n";
        cout<<"0. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            break;
        case 1:
            loginCustomer();
            break;
        case 2:
            loginAdmin();
            break;
        default:
            cout<<"Invalid choice\n";
        }
    }
    while(choice != 0);
    endProgram();
    return 0;
}
