#include <iostream>
using namespace std;

int& highestMark(int marks[], int size) {
    int highest = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[highest]) highest = i;
    return marks[highest];
}
const int& highestMarkConst(const int marks[], int size) {
    int highest = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[highest]) highest = i;
    return marks[highest];
}
int highestMarkCopy(const int marks[], int size) {
    int highest = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[highest]) highest = i;
    return marks[highest];
}
// Intentionally unsafe example; do not call this function.
int& danglingReference() {
    int local = 50;
    return local; // Compiler warning: returning reference to local variable
}
int main() {
    int marks[] = {75, 88, 92, 81, 95};
    int size = 5;
    cout << "Highest mark: " << highestMark(marks, size) << '\n';
    highestMark(marks, size) += 2;
    cout << "After moderation: " << highestMark(marks, size) << '\n';
    cout << "Const reference: " << highestMarkConst(marks, size) << '\n';
    cout << "Returned copy: " << highestMarkCopy(marks, size) << '\n';
}