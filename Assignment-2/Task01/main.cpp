#include <iostream>
using namespace std;

void change(int a, int& b, int* c) {
    a += 10;
    b += 10;
    *c += 10;
}
int& bigger(int& p, int& q) { return p > q ? p : q; }
void show(int x, int y = 5, int z = 10) { cout << x + y + z << ' '; }

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}
void applyConcession(long long& fee, int percent) {
    fee -= fee * percent / 100;
}
void applyByPointer(long long* fee, int percent) {
    if (fee) *fee -= *fee * percent / 100;
}
long long concessionResult(long long fee, int percent) {
    return fee - fee * percent / 100;
}
int main() {
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    cout << a << ' ' << b << ' ' << c << '\n';
    bigger(a, c) = 100;
    cout << a << ' ' << c << '\n';
    show(1); show(1, 2); show(1, 2, 3); cout << '\n';

    long long value = 45000, reference = 45000, pointer = 45000;
    applyByValue(value, 10);
    applyConcession(reference, 10);
    applyByPointer(&pointer, 10);
    cout << "Value: " << value << '\n';
    cout << "Reference: " << reference << '\n';
    cout << "Pointer: " << pointer << '\n';
    cout << "Returned: " << concessionResult(45000, 10) << '\n';
}