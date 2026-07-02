#include <iostream>
#include <vector>
#include<string>
using namespace std;

// Transaction Class
class Transaction
{
public:
    string type;
    double amount;

    Transaction(string t, double a)
    {
        type = t;
        amount = a;
    }
};

// Account Class
class Account
{
public:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

    Account(int accNo, double bal)
    {
        accountNumber = accNo;
        balance = bal;
    }
};

// Customer Class
class Customer
{
public:
    string name;
    Account account;

    Customer(string n, int accNo, double bal)
        : account(accNo, bal)
    {
        name = n;
    }
};

vector<Customer> customers;

// Find Account
int findAccount(int accNo)
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i].account.accountNumber == accNo)
            return i;
    }
    return -1;
}

// Create Customer
void createCustomer()
{
    string name;
    int accNo;
    double balance;

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Initial Balance: ";
    cin >> balance;

    customers.push_back(Customer(name, accNo, balance));

    cout << "Account Created Successfully!\n";
}

// Deposit
void depositMoney()
{
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    int index = findAccount(accNo);

    if (index == -1)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    customers[index].account.balance += amount;
    customers[index].account.transactions.push_back(
        Transaction("Deposit", amount));

    cout << "Deposit Successful!\n";
}

// Withdraw
void withdrawMoney()
{
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    int index = findAccount(accNo);

    if (index == -1)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    if (amount > customers[index].account.balance)
    {
        cout << "Insufficient Balance!\n";
        return;
    }

    customers[index].account.balance -= amount;
    customers[index].account.transactions.push_back(
        Transaction("Withdraw", amount));

    cout << "Withdrawal Successful!\n";
}

// Transfer
void transferMoney()
{
    int sender, receiver;
    double amount;

    cout << "Sender Account: ";
    cin >> sender;

    cout << "Receiver Account: ";
    cin >> receiver;

    cout << "Amount: ";
    cin >> amount;

    int s = findAccount(sender);
    int r = findAccount(receiver);

    if (s == -1 || r == -1)
    {
        cout << "Invalid Account Number!\n";
        return;
    }

    if (customers[s].account.balance < amount)
    {
        cout << "Insufficient Balance!\n";
        return;
    }

    customers[s].account.balance -= amount;
    customers[r].account.balance += amount;

    customers[s].account.transactions.push_back(
        Transaction("Transfer Sent", amount));

    customers[r].account.transactions.push_back(
        Transaction("Transfer Received", amount));

    cout << "Transfer Successful!\n";
}

// Show Details
void showDetails()
{
    int accNo;

    cout << "Enter Account Number: ";
    cin >> accNo;

    int index = findAccount(accNo);

    if (index == -1)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "\nName: " << customers[index].name;
    cout << "\nAccount No: "
         << customers[index].account.accountNumber;
    cout << "\nBalance: "
         << customers[index].account.balance << endl;
}

// Transaction History
void showHistory()
{
    int accNo;

    cout << "Enter Account Number: ";
    cin >> accNo;

    int index = findAccount(accNo);

    if (index == -1)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "\nTransaction History:\n";

    for (Transaction t :
         customers[index].account.transactions)
    {
        cout << t.type
             << " : "
             << t.amount << endl;
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n===== BANK SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Show Details\n";
        cout << "6. Transaction History\n";
        cout << "7. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createCustomer();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            transferMoney();
            break;
        case 5:
            showDetails();
            break;
        case 6:
            showHistory();
            break;
        case 7:
            cout << "Thank You!\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}