#include <iostream>
using namespace std;

// Returns a reference to an element that remains alive in the caller's array.
int& highestMark(int marks[], int size) {
    int best = 0;
    for (int i = 1; i < size; ++i) if (marks[i] > marks[best]) best = i;
    return marks[best];
}

// Unsafe example for explanation only: never use a reference to a local variable.
int& danglingReference() {
    int local = 42;
    return local; // Undefined behaviour if the returned reference is used.
}

int main() {
    int marks[] = {78, 91, 86, 95, 88};
    int& top = highestMark(marks, 5);
    cout << "Highest mark: " << top << '\n';
    top = 99;
    cout << "Updated highest mark: " << marks[3] << '\n';
    cout << "Use const int& when the caller must not modify the selected value.\n";
}
