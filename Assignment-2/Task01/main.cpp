#include <iostream>
using namespace std;

// Call by value: only the local copy is modified.
void applyByValue(long long fee, int percent = 10) {
    fee -= fee * percent / 100;
    cout << "Inside call by value: " << fee << '\n';
}

// Call by reference: the original variable is modified.
void applyByReference(long long& fee, int percent = 10) {
    fee -= fee * percent / 100;
}

// Call by pointer: the pointed-to variable is modified.
void applyByPointer(long long* fee, int percent = 10) {
    if (fee != nullptr) *fee -= *fee * percent / 100;
}

int main() {
    long long byValue = 45000, byReference = 45000, byPointer = 45000;
    applyByValue(byValue);
    applyByReference(byReference);
    applyByPointer(&byPointer);
    cout << "After call by value: " << byValue << '\n';
    cout << "After call by reference: " << byReference << '\n';
    cout << "After call by pointer: " << byPointer << '\n';
}
