# Assignment 3 – CO3

**Name:** ____________________  
**Register Number:** ____________________  
**GitHub:** https://github.com/krishnasashank1403-beep/DSA0116

## Q1 – Constructors and Constructor Overloading

A Book record needs a title, author and number of copies. I would provide a default constructor for an empty record, a title-only constructor for donated books, and a full constructor for books with all details. The constructors should use member initializer lists, and the title-only constructor can call the full constructor so the validation is written only once.

```cpp
#include <iostream>
#include <string>
#include <stdexcept>
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
    void print() const {
        cout << title << " | " << author << " | " << copies << '\\n';
    }
};

int main() {
    Book empty;
    Book donated("The Alchemist");
    Book full("Wings of Fire", "A.P.J. Abdul Kalam", 5);
    empty.print(); donated.print(); full.print();
}
```

The compiler supplies a default constructor only when no constructor has been declared by the programmer. Once a parameterised constructor is written, the compiler does not automatically add a no-argument constructor. Member initializer lists are better than assigning values inside the body because members are constructed directly. Members are initialized in the order in which they are declared in the class, not the order written in the initializer list.

The three objects above represent an empty record, a donated book and a fully entered book. A negative copy count is rejected. The title-only constructor is marked `explicit` so a string cannot be converted into a Book without the programmer asking for it.

Using one constructor with default arguments is also possible. It would still take O(1) time and O(1) extra space to create a Book. Separate overloads make the different creation cases clearer, while constructor delegation keeps validation in one place.

## Q2 – Copy Constructors: Shallow and Deep Copies

A Prescription stores medicine names in a dynamically allocated array. A normal compiler-generated copy copies the pointer, not the array. Both objects then point to the same memory. Changing one prescription affects the other, and both destructors may try to delete the same array.

A deep copy creates a separate array and copies each medicine name. The copy constructor, copy assignment operator and destructor are connected; this is called the Rule of Three.

```cpp
#include <iostream>
#include <string>
using namespace std;

class Prescription {
    int n;
    string* medicines;
public:
    explicit Prescription(int count)
        : n(count), medicines(new string[count]{}) {}

    Prescription(const Prescription& other)
        : n(other.n), medicines(new string[other.n]) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
    }

    Prescription& operator=(const Prescription& other) {
        if (this == &other) return *this;
        string* copy = new string[other.n];
        for (int i = 0; i < other.n; ++i) copy[i] = other.medicines[i];
        delete[] medicines;
        medicines = copy;
        n = other.n;
        return *this;
    }

    ~Prescription() { delete[] medicines; }

    void set(int i, const string& medicine) { medicines[i] = medicine; }
    string get(int i) const { return medicines[i]; }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");
    Prescription q = p;
    q.set(1, "Cetirizine");
    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");
    cout << p.get(0) << ' ' << p.get(1) << " | "
         << q.get(0) << ' ' << q.get(1) << " | "
         << r.get(0) << ' ' << r.get(1) << '\\n';
}
```

Output:

```text
Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS
```

The copy constructor is used when an object is initialized from another object, passed by value, or returned by value when copy elision does not remove the copy. Passing by const reference avoids making a copy. Copying n medicine names takes O(n) time and O(n) space. A shallow pointer copy is O(1), but it is not safe for owning dynamically allocated memory. If a vector is used instead of a raw pointer, its generated copy already performs a deep copy and the class can follow the Rule of Zero.

## Q3 – Dynamic Constructors and Destructors

The seat map size is known only when an event is created, so dynamic memory is useful. Each row can be allocated separately, and the destructor must release every row and then the row pointer array.

```cpp
#include <iostream>
using namespace std;

class Event {
    int rows, seats;
    char** map;
    int booked = 0;
public:
    Event(int r, int s) : rows(r), seats(s), map(nullptr) {
        if (rows <= 0 || seats <= 0) return;
        map = new char*[rows];
        int made = 0;
        try {
            for (; made < rows; ++made) {
                map[made] = new char[seats];
                for (int j = 0; j < seats; ++j) map[made][j] = 'O';
            }
        } catch (...) {
            while (made > 0) delete[] map[--made];
            delete[] map;
            throw;
        }
        cout << "Event opened\\n";
    }
    bool book(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats ||
            map[r][s] == 'X') return false;
        map[r][s] = 'X'; ++booked; return true;
    }
    bool cancel(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats ||
            map[r][s] == 'O') return false;
        map[r][s] = 'O'; --booked; return true;
    }
    ~Event() {
        if (map) {
            for (int i = 0; i < rows; ++i) delete[] map[i];
            delete[] map;
        }
        cout << "Event closed. Seats booked: " << booked << '\\n';
    }
};

int main() {
    Event morning(2, 3);
    morning.book(0, 1);
    {
        Event afternoon(1, 2);
        afternoon.book(0, 0);
    }
    Event* special = new Event(2, 2);
    special->book(1, 1);
    delete special;
}
```

Local objects are destroyed when their scope ends. An object inside a block is destroyed at the closing brace. A dynamically created object remains until `delete` is called. Forgetting delete causes a memory leak, while using `delete` instead of `delete[]` for an array is undefined behaviour. A destructor has no return type, takes no arguments and cannot be overloaded because there is only one destruction operation for an object.

The logger program in the question prints:

```text
+A +B -B copyAc use -Ac +P -P end -A
```

The copy is made when `a` is passed by value to `use`, and that temporary copy is destroyed when the function call finishes. The heap object P is destroyed by `delete`. The local objects are destroyed in reverse order of their construction.

A single contiguous block or a vector of vectors can also represent the seat map. Access is O(1) in either design. A contiguous block needs one allocation and avoids row pointers; separate row allocations need rows + 1 allocations. The destructor ties cleanup to object lifetime, which is the basic RAII idea.

## Q4 – Overloading Arithmetic and Stream Operators

Money should be stored as an integer number of paise. This avoids floating-point rounding when adding or comparing amounts. The plus operator returns a new object, while plus-equals changes the current object and returns a reference to it.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

class Money {
    long long paise;
    Money(long long totalPaise, bool) : paise(totalPaise) {}
public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        return Money(paise + other.paise, true);
    }
    bool operator==(const Money& other) const {
        return paise == other.paise;
    }
    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Money& m) {
        long long absolute = m.paise < 0 ? -m.paise : m.paise;
        if (m.paise < 0) out << '-';
        return out << "Rs " << absolute / 100 << '.'
                   << setw(2) << setfill('0') << absolute % 100
                   << setfill(' ');
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\\n' << boolalpha << (c == Money(200)) << '\\n';
    cout << Money(0, 75) + Money(0, 50) << '\\n';
}
```

Output:

```text
Rs 200.00
true
Rs 1.25
```

The stream insertion operator is a non-member because the left operand is the output stream, not Money. It is a friend so it can read the private paise value. An expression such as `a + b` is treated like a call to `a.operator+(b)` for a member overload. Addition and comparison take O(1) time and O(1) extra space. Multiplying one Money value by another does not usually make sense; multiplying by a quantity or percentage is more useful.

## Q5 – Overloading Increment, Comparison and Subscript Operators

Prefix increment changes the object and returns it by reference. Postfix increment saves the old value, changes the object and returns the saved copy. The extra copy is why prefix is generally preferred for class objects when the old value is not needed.

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Time {
    int seconds;
public:
    explicit Time(int s = 0) : seconds(s) {}
    Time& operator++() { ++seconds; return *this; }
    Time operator++(int) { Time old(*this); ++seconds; return old; }
    bool operator==(const Time& t) const { return seconds == t.seconds; }
    bool operator<(const Time& t) const { return seconds < t.seconds; }
    void print() const {
        cout << seconds / 3600 << ':'
             << (seconds / 60) % 60 << ':'
             << seconds % 60 << '\\n';
    }
};

class Playlist {
    vector<string> tracks;
public:
    explicit Playlist(vector<string> t) : tracks(move(t)) {}
    string& operator[](int i) {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw out_of_range("Track index out of range");
        return tracks[i];
    }
    const string& operator[](int i) const {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw out_of_range("Track index out of range");
        return tracks[i];
    }
};

int main() {
    Time t(3599);
    Time a = t++;
    Time b = ++t;
    a.print(); b.print(); t.print();
    Playlist p({"Song One", "Song Two"});
    cout << p[0] << '\\n';
}
```

In the prediction program, `a = c++` stores the old value 5 and then c becomes 6. `b = ++c` increments c to 7 and stores 7. The output is:

```text
5 7 7
```

The compiler distinguishes postfix increment by its dummy int parameter. The non-const subscript overload allows an item to be changed, while the const version allows safe reading from a const playlist. An invalid index should be reported, for example by throwing `out_of_range`. Access is O(1); the range check adds one comparison.

## Q6 – The Rules of Operator Overloading

A Text class that owns a dynamic character array needs a copy constructor, copy assignment operator and destructor. These make sure each object manages its own memory. The assignment operator must be a member function. Concatenation and comparison can be members, while stream insertion is usually a friend non-member.

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Text {
    char* data;
public:
    Text(const char* s = "") {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }
    Text(const Text& other) : Text(other.data) {}
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* copy = new char[strlen(other.data) + 1];
            strcpy(copy, other.data);
            delete[] data;
            data = copy;
        }
        return *this;
    }
    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        size_t n = strlen(data) + strlen(other.data);
        char* joined = new char[n + 1];
        strcpy(joined, data);
        strcat(joined, other.data);
        Text result(joined);
        delete[] joined;
        return result;
    }
    bool operator==(const Text& other) const {
        return strcmp(data, other.data) == 0;
    }
    bool operator!=(const Text& other) const { return !(*this == other); }
    friend ostream& operator<<(ostream& out, const Text& t) {
        return out << t.data;
    }
};

int main() {
    Text first("Hello "), second("Metro");
    Text message = first + second;
    cout << message << '\\n';
    Text copy;
    copy = message;
    copy = copy;
    cout << boolalpha << (copy == message) << '\\n';
}
```

The operators `::`, `.`, `.*`, `?:` and `sizeof` cannot be overloaded. Operator overloading cannot change an operator's precedence or number of operands, and at least one operand must be a user-defined type. The assignment operator must be a member. A friend is useful when a non-member function needs access to private data, such as stream insertion.

For `a + b + c`, temporary Text objects may be created as the first result is combined with c. Concatenation copies the characters into new storage. Replacing the class with std::string is usually better for normal application code because it already manages memory and copying safely. A well-designed += operation on a temporary can reduce unnecessary intermediate allocations.

## Q7 – Design a Complex-Number Class

An impedance can be represented by a real part and an imaginary part. A resistor has impedance R + 0j, an inductor has 0 + jωL, and a capacitor has 0 − j/(ωC). Series impedances are added. Parallel impedance is calculated using (Z1 × Z2) / (Z1 + Z2).

```cpp
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Complex {
    double real, imag;
public:
    Complex() : real(0), imag(0) {}
    Complex(double r) : real(r), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& z) const {
        return {real + z.real, imag + z.imag};
    }
    Complex operator-(const Complex& z) const {
        return {real - z.real, imag - z.imag};
    }
    Complex operator*(const Complex& z) const {
        return {real*z.real - imag*z.imag,
                real*z.imag + imag*z.real};
    }
    Complex operator/(const Complex& z) const {
        double d = z.real*z.real + z.imag*z.imag;
        if (d == 0) throw runtime_error("Division by zero impedance");
        return {(real*z.real + imag*z.imag)/d,
                (imag*z.real - real*z.imag)/d};
    }
    bool operator==(const Complex& z) const {
        return real == z.real && imag == z.imag;
    }
    double magnitude() const { return sqrt(real*real + imag*imag); }
    friend ostream& operator<<(ostream& out, const Complex& z) {
        return out << z.real << (z.imag < 0 ? " - j" : " + j")
                   << abs(z.imag);
    }
};

int main() {
    Complex resistor(10, 0);
    Complex inductor(0, 5);
    Complex capacitor(0, -2);

    Complex series = resistor + inductor + capacitor;
    Complex parallel = (resistor * inductor) / (resistor + inductor);

    cout << "Series: " << series << '\\n';
    cout << "Magnitude: " << series.magnitude() << '\\n';
    cout << "Parallel: " << parallel << '\\n';
    try {
        Complex zero;
        cout << resistor / zero;
    } catch (const exception& e) {
        cout << e.what() << '\\n';
    }
}
```

For the example, the series impedance is 10 + j3 and its magnitude is approximately 10.44. For the resistor 10 + j0 in parallel with the inductor 0 + j5, the result is 2 + j4. Division by a zero impedance is checked and reported instead of allowing an invalid result.

Each arithmetic operation takes O(1) time and uses O(1) space. The class is useful for learning how the operations work, but `std::complex<double>` is preferable in most real projects because it is already tested and provides standard complex arithmetic. A remaining limitation of this simple class is that exact floating-point equality can be unreliable for calculated values; a tolerance comparison would be better.
