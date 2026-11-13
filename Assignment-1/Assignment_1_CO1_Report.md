# ASSIGNMENT 1

**OBJECT-ORIENTED PROGRAMMING USING C++**

**CO1 – Namma Metro Smart-Card Fare System**

| Name | P . Krishna Sashank |
| --- | --- |
| Register Number | 192525191 |
| Course id | DSA0116 |
| Repository | https://github.com/krishnasashank1403-beep/DSA0116 |

## Task 1 – Understand the Problem and Identify the Objects

The metro system has to calculate the fare based on the farthest zone a passenger travels to. Inner, Middle and Outer zone fares are Rs 10, Rs 20 and Rs 30. During peak hours, a 20% surcharge is added. After paying, the smart card must still have at least Rs 50. Students and senior citizens can receive a concession.

I would use a few main objects. A SmartCard stores the card number and balance, and it can check whether a journey is affordable and deduct the fare. A Passenger stores details such as passenger type and concession eligibility. A Journey keeps the source, destination, time and fare for one trip. Zone represents the area travelled, and FareTable stores the base fares and surcharge rules.

Keeping the balance private in SmartCard is useful because other parts of the program should not directly change it to an invalid value. The FareTable keeps fare values in one place, so a change does not require searching through the whole program. Passenger can be extended for student and senior-citizen categories, while a common fare calculation interface can handle their different concessions. Encapsulation protects the card balance, abstraction hides the calculation details, inheritance can represent passenger categories, and polymorphism can be used when different passenger types calculate concessions differently.

A valid journey must have a known zone, a valid time, a non-negative fare and enough money on the card. Once the fare is deducted, the remaining balance cannot be below Rs 50. Peak time is from 8:00 AM to before 10:00 AM, and from 5:00 PM to before 8:00 PM. So 10:00 AM and 8:00 PM are not peak times.

In a procedural design, the same information could be stored in variables and processed using separate functions. Both designs take O(1) time for one fare calculation and use O(1) memory per card. The bigger difference is maintenance: if a rule changes, an object-oriented design keeps the related data and behaviour together, so fewer unrelated parts need editing.

## Task 2 – Use Tokens, Keywords, Identifiers and Constants Correctly

C++ uses keywords such as int, class, return and switch. Identifiers are the names given by the programmer, for example SmartCard, balance and calculateFare. Constants are fixed values such as the minimum balance. Operators include +, -, *, / and ==. Punctuators include braces, parentheses, commas and semicolons.

I would use constexpr for values that are known while compiling, such as the base fare for each zone and the peak surcharge percentage. Compared with #define, constexpr has a type and follows normal C++ scope rules. const is useful for values that should not change after initialization, even when their value is not known at compile time. enum class Zone { Inner, Middle, Outer } makes zone values clear and prevents accidental mixing with ordinary integers.

```cpp
enum class Zone { Inner, Middle, Outer };
constexpr long long BASE_FARE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;
```

Names should explain what the value is used for. I use PascalCase for class and enum names, and camelCase or descriptive lowercase names for functions and variables. A macro does not have a C++ type or normal scope, while constexpr values do. Neither usually needs separate runtime storage when used as a compile-time constant, and this choice does not change the O(1) fare calculation time.

## Task 3 – Choose Data Types and Check Type Compatibility

Money should be stored as integer paise instead of double rupees. For example, Rs 10.50 is stored as 1050 paise. This avoids small floating-point rounding differences when fares are added or deducted. The card balance and total collection can use long long because the network processes many journeys.

| Value | Suggested type | Reason |
| --- | --- | --- |
| Fare and balance | long long (paise) | Exact whole-number money values and large totals |
| Peak or concession flag | bool | Only true or false |
| Zone | enum class Zone | Clear set of allowed zone values |
| Hour | int | Whole hour from 0 to 23 |
| Journey count | long long | Large network-level counts |
| Station code | char or string | Depends on the code format |

The exact sizeof values depend on the compiler and machine. On a typical 64-bit g++ system, bool and char are 1 byte, int is 4 bytes, and long long and double are 8 bytes. float is usually 4 bytes. The program can print sizeof(type) on the actual system to confirm it.

When int, double and bool appear in one expression, C++ applies integer promotions and usual arithmetic conversions. For example, int plus double is evaluated as double. A bool used in arithmetic becomes 0 or 1. An int is enough for a small individual fare, but a network collection can exceed its maximum range. For three million Rs 30 journeys, the total is Rs 90,000,000 (900 crore? No: Rs 9 crore), which fits in a signed 32-bit int, but larger totals or paise totals require care. In paise this example is 9,000,000,000, which does not fit in a signed 32-bit int, so long long is the safer choice.

Using double rupees would still take O(1) time and normally 8 bytes per value, but binary floating point cannot represent every decimal fraction exactly. With integer paise, addition and subtraction stay exact as long as the chosen integer type does not overflow.

## Task 4 – Control Implicit Conversions

An implicit conversion happens when C++ changes a value to another type without an explicit cast. For example, assigning an int expression to double converts the result to double, but it does not recover any fraction already lost through integer division. A char can be promoted to int during arithmetic. A non-zero integer converts to true when stored in bool. Comparing signed and unsigned integers can convert the signed value to unsigned, which can cause surprising results.

Brace initialization helps prevent narrowing conversions. For example, int value{3.7}; is rejected by the compiler because a double would lose information when stored as int. static_cast is useful when a conversion is intentional and should be visible in the code.

```cpp
int a = 7, b = 2;
double c = a / b;
double d = static_cast<double>(a) / b;
std::cout << c << ' ' << d << '\\n';
char ch = 'A' + 2;
std::cout << ch << ' ' << ch + 1 << '\\n';
bool flag = 5;
std::cout << flag << ' ' << std::boolalpha << flag << '\\n';
unsigned int u = 1;
int s = -1;
std::cout << (s < u ? "s < u" : "s >= u") << '\\n';
```

The output is 3 3.5 because a / b is integer division and gives 3 before it is assigned to double. The explicit cast makes the division floating point. The character expression prints C, followed by 68 because ch is promoted to its integer character code before adding 1. The bool line prints 1 true: the integer 5 converts to true, and boolalpha changes the second display to a word. For the signed/unsigned comparison, -1 is converted to a large unsigned value, so the comparison is false and the program prints s >= u.

Using explicit casts and brace initialization makes these conversion points clearer and can catch narrowing mistakes at compile time. It does not change the O(1) time or storage required for these simple values.

## Task 5 – Write Correct Expressions with the Right Precedence

The peak-hour expression should be written as (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20). Parentheses make the two time ranges easy to read. The surcharge can be calculated with fare += fare * 20 / 100, using integer paise. A concession can be applied similarly after checking the passenger type.

In x++, the current value is used before the increment. In ++x, the value is incremented before it is used. Writing i = i++ should be avoided because it is confusing and can lead to undefined or unsequenced behaviour depending on the expression and language version. For integer division with negative values, C++ truncates toward zero; the remainder has the sign of the left operand.

For the supplied program, the output is:

```text
11 16
9 6 4
6 4
3 1 -3 -1
18
```

First, multiplication happens before addition, so 5 + 3 * 2 is 11, while (5 + 3) * 2 is 16. Next, x++ uses 5 and then increments x to 6; ++y first increments y from 3 to 4 and then uses 4, so z becomes 9. The next line prints the larger of x and y (6), and x % 4 * 2 is evaluated left to right for equal-precedence multiplicative operators, giving 2 * 2 = 4. Integer division gives 3 and remainder 1 for 10 / 3 and 10 % 3; for -10, the quotient is -3 and remainder is -1. The loop adds 0, 3, 6 and 9, giving 18.

A lookup table with 24 bool values could store whether each hour is peak. The time for a check is O(1) either way. The table makes checking direct but uses about 24 bool elements, and the expression version uses no table.

## Task 6 – Design the Control Structures

I would use switch to select the base fare for a zone, and if statements to check peak time and whether the card has enough balance. A loop can process each journey. A range-based for loop is suitable when the journeys are already stored in an array or container. continue can skip an invalid journey, and break can stop processing if the input is no longer usable.

Pseudocode:

```text
START
Read zone, hour, and card balance
Select base fare using zone
IF hour is between 8 and 10 (excluding 10)
OR hour is between 17 and 20 (excluding 20)
Add 20 percent surcharge
ENDIF
IF balance - fare is at least 5000 paise
Deduct fare
Print fare and remaining balance
ELSE
Print journey denied
ENDIF
END
```

```cpp
long long fare(Zone zone, bool peak) {
    long long amount = 0;
    switch (zone) {
        case Zone::Inner:  amount = 1000; break;
        case Zone::Middle: amount = 2000; break;
        case Zone::Outer:  amount = 3000; break;
    }
    if (peak) amount += amount * 20 / 100;
    return amount;
}

bool canTravel(long long balance, long long amount) {
    return balance - amount >= 5000;
}
```

For the supplied trips, the fares are Rs 10.00, Rs 36.00 and the third journey is denied because paying Rs 20 would leave less than Rs 50. The remaining balance after the first two journeys is Rs 54.

A fare array indexed by the zone is another O(1) option. It uses a small fixed amount of memory and can be easier to extend when more zones are added, while switch gives each case a clear named branch. With a fourth zone, both the enum and the fare data or switch must be updated.

## Task 7 – From Procedural to Object-Oriented

In a procedural version, the balance is stored in a variable and free functions check and deduct the fare. In an object-oriented version, SmartCard stores the balance as a private member and provides canTravel() and deduct() functions. This prevents unrelated code from directly setting the balance to a negative value.

```cpp
class SmartCard {
private:
    long long balancePaise;
    static constexpr long long minimumPaise = 5000;
public:
    explicit SmartCard(long long openingBalance)
        : balancePaise(openingBalance) {}

    bool canTravel(long long farePaise) const {
        return farePaise >= 0 && balancePaise - farePaise >= minimumPaise;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }

    long long balance() const { return balancePaise; }
};
```

Both styles take O(1) time for a balance check or deduction and use O(1) memory per card. If the balance were public, any part of the program could change it without checking the Rs 50 rule. Keeping it private makes the rule easier to protect and maintain.

## Task 8 – Read and Print Data Safely

The gate program should check whether each input was read correctly. If the operator enters letters where a number is expected, cin enters a failed state. The program should use cin.clear() to reset the state and ignore the rest of the invalid line before asking again. Money should be printed with fixed and setprecision(2), or formatted from integer paise.

```cpp
#include <iostream>
#include <limits>
#include <iomanip>

int main() {
    int hour;
    while (true) {
        std::cout << "Enter hour (0-23): ";
        if (std::cin >> hour && hour >= 0 && hour <= 23) break;
        std::cout << "Invalid input. Try again.\\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');
    }
    double rupees = 10.5;
    std::cout << "Fare: Rs " << std::fixed << std::setprecision(2)
              << rupees << '\\n';
}
```

Another approach is to read a full line with getline() and convert it using stoi() inside try/catch. Both approaches process a line in O(L) time in relation to its length. getline gives more control over the full input line, while cin is convenient for straightforward numeric values. In either approach, invalid input should not be allowed to continue into the fare calculation.

## Task 9 – Implement and Test the Fare Logic

The fare logic should be checked for all three zones in peak and off-peak hours. Boundary times are important: 8:00 and 17:00 are peak, while 10:00 and 20:00 are not. A card should be allowed to travel when the balance after deduction is exactly Rs 50. It should be denied when the remaining balance would be Rs 49.99 or lower.

| Case | Expected result |
| --- | --- |
| Inner, off-peak | Rs 10.00 |
| Middle, off-peak | Rs 20.00 |
| Outer, off-peak | Rs 30.00 |
| Inner, 08:00 | Rs 12.00 |
| Outer, 17:00 | Rs 36.00 |
| 10:00 or 20:00 | No peak surcharge |
| Balance exactly fare + Rs 50 | Journey allowed |
| Balance below fare + Rs 50 | Journey denied |
| Unknown zone or negative recharge | Input rejected |
| Letters entered for hour | Input error handled and input requested again |

A table-driven test can store inputs and expected results, then run each case in a loop. For t test cases the time is O(t), and the test table uses O(t) space. Adding a new boundary test is simple because another row can be added without writing a new test block.

## Task 10 – Compare Expectations with Execution

The total should be accumulated in integer paise using long long. For example, if every one of 3,000,000 journeys costs Rs 30, the total is Rs 90,000,000 or 9,000,000,000 paise. The paise total is larger than the maximum value of a signed 32-bit int, so int is not suitable for the network-wide paise total. long long can store it safely.

Using double may display a decimal total that looks correct for many inputs, but floating-point representation can introduce small differences when values are repeatedly added. Integer paise gives an exact result as long as the total remains within the range of long long. The time per addition is O(1) for int, long long and double; the main difference is range and exactness.

## Task 11 – Recommend and Defend the Final Design

I would keep the fare values in one constexpr fare table, use enum class for zones, and store all money as long long paise. SmartCard should keep its balance private and provide functions to check and deduct a fare. A separate FareTable or fare calculation function should handle the base fare and peak surcharge. The passenger type can be represented separately so concessions do not become mixed into the card balance logic.

This design is suitable for a larger network because each fare calculation and balance update takes O(1) time. The main limitation is that any new fare rule still needs to be tested carefully, especially where discounts and surcharges interact. If fares change often, reading them from a configuration file at program start can avoid recompiling the program. Reading z zone values takes O(z) startup time and O(z) storage, but it makes incorrect or missing configuration values something the program must validate.

## Task 12 – Re-evaluate and Adapt the Design

The updated system has an Airport zone with a fare of Rs 60, a 10% weekend discount that cannot be combined with the peak surcharge, and a monthly pass that allows unlimited journeys in two selected zones. The original three-zone switch must be updated, and the fare rules should be separated so discounts and passes can be applied in a clear order.

I would modify the design rather than replace everything. The SmartCard class can still manage the stored balance, while a FareTable holds four base fares. A separate Pass class stores the two zones covered by the monthly pass. The fare calculation first checks whether the passenger has a valid pass for the journey. If there is no pass, it selects the base fare, then applies either the weekend discount or the peak surcharge, but never both.

```cpp
enum class Zone { Inner, Middle, Outer, Airport };
constexpr long long FARE_PAISE[] = {1000, 2000, 3000, 6000};

long long calculateFare(Zone zone, bool peak, bool weekend) {
    long long fare = FARE_PAISE[static_cast<int>(zone)];
    if (weekend) {
        fare -= fare * 10 / 100;
    } else if (peak) {
        fare += fare * 20 / 100;
    }
    return fare;
}

class Pass {
    Zone first;
    Zone second;
public:
    Pass(Zone a, Zone b) : first(a), second(b) {}
    bool covers(Zone z) const { return z == first || z == second; }
};
```

For example, an Airport trip normally costs Rs 60. During peak time on a weekday it costs Rs 72. On a weekend it costs Rs 54, even if the travel time falls in peak hours, because the weekend discount does not combine with the surcharge. A pass covering Airport makes the covered journey free under the stated unlimited-journey rule. The SmartCard still needs to enforce the minimum balance for journeys that are paid using the stored-value card; the assignment brief does not specify whether pass journeys should be subject to the Rs 50 minimum, so that detail should be confirmed before final implementation.

The fare table makes adding the fourth zone straightforward. Separating the discount and pass logic keeps the new rules easier to change later. The main thing to test is that a weekend journey receives only the discount and never both adjustments.