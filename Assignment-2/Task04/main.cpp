#include <iostream>
#include <string>
using namespace std;

class SavingsAccount {
private:
    int accountNumber;
    double balance;
    string transactions[10];
    int count;
    int nextIndex;

    void record(const string& entry) {
        transactions[nextIndex] = entry;
        nextIndex = (nextIndex + 1) % 10;
        if (count < 10) ++count;
    }
public:
    SavingsAccount(int number, double openingBalance)
        : accountNumber(number), balance(openingBalance), count(0), nextIndex(0) {}
    void deposit(double amount);
    void withdraw(double amount);
    void miniStatement() const;
    double getBalance() const { return balance; }
};

void SavingsAccount::deposit(double amount) {
    if (amount <= 0) { cout << "Invalid deposit\n"; return; }
    balance += amount;
    record("Deposit: " + to_string(amount));
}
void SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) { cout << "Invalid withdrawal\n"; return; }
    balance -= amount;
    record("Withdrawal: " + to_string(amount));
}
void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << "\nBalance: " << balance
         << "\nRecent transactions (oldest to newest):\n";
    int start = (count == 10) ? nextIndex : 0;
    for (int i = 0; i < count; ++i)
        cout << transactions[(start + i) % 10] << '\n';
}
int main() {
    SavingsAccount account(1001, 5000);
    account.deposit(1000);
    account.withdraw(500);
    account.deposit(200);
    account.withdraw(100);
    for (int i = 1; i <= 8; ++i) account.deposit(i * 100);
    account.miniStatement();
}