#include <iostream>
using namespace std;

struct Parcel { double weightKg; bool express; bool insured; };

double charge(int grams, bool express = false) {
    double total = 40.0 + (grams / 1000.0) * 20.0;
    if (express) total += 30.0;
    return total;
}
double charge(double kg, bool express = false, bool insured = false) {
    double total = 40.0 + kg * 20.0;
    if (express) total += 30.0;
    if (insured) total += 15.0;
    return total;
}
double charge(float kg, bool express = false, bool insured = false) {
    return charge(static_cast<double>(kg), express, insured);
}
double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}
int main() {
    cout << "charge(2): " << charge(2) << '\n';
    cout << "charge(2.0): " << charge(2.0) << '\n';
    cout << "charge(2.0f): " << charge(2.0f) << '\n';
    cout << "charge(2000,true): " << charge(2000, true) << '\n';
    cout << "charge(2.5,true,true): " << charge(2.5, true, true) << '\n';
    Parcel p{3.0, false, true};
    cout << "charge(parcel): " << charge(p) << '\n';
}