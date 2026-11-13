#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
class Book {
    string title, author;
    int copies;
public:
    Book() : Book("", "Unknown", 0) {}
    explicit Book(const string& t) : Book(t, "Unknown", 1) {}
    Book(const string& t, const string& a, int c)
        : title(t), author(a), copies(c) {
        if (c < 0) throw invalid_argument("Copies cannot be negative");
    }
    void print() const { cout << title << " | " << author << " | " << copies << '\n'; }
};
int main() {
    Book empty;
    Book donated("The Alchemist");
    Book full("Wings of Fire", "A.P.J. Abdul Kalam", 5);
    empty.print(); donated.print(); full.print();
    try { Book invalid("Bad record", "Unknown", -1); }
    catch (const invalid_argument& e) { cout << e.what() << '\n'; }
}