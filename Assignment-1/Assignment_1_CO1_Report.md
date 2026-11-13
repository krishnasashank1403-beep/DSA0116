# Assignment 1 – CO1
## Namma Metro Smart-Card Fare System

**Name:** ____________________  
**Register Number:** ____________________  
**Course:** B.Tech – Artificial Intelligence and Machine Learning  
**GitHub:** https://github.com/krishnasashank1403-beep/DSA0116

## Task 1 – Understand the Problem and Identify the Objects

The metro fare depends on the farthest zone travelled. Inner, Middle and Outer cost Rs 10, Rs 20 and Rs 30. A 20% surcharge is added during peak hours. After paying the fare, the card must still have at least Rs 50. Students and senior citizens receive concessions.

I would use a few objects for this system. A **SmartCard** stores the card number and balance, and checks whether a journey is affordable before deducting the fare. A **Passenger** stores the passenger type and concession details. A **Journey** keeps the travel information, such as the zone and time. A **Zone** represents the area travelled, while a **FareTable** keeps the base fares and surcharge details.

Keeping the balance private in SmartCard helps prevent other parts of the program from changing it incorrectly. FareTable keeps the prices in one place, so a fare revision is easier. Inheritance could be used for student and senior-citizen passenger types. Polymorphism can be used when their concession rules differ. Encapsulation protects the balance, while abstraction hides the internal fare calculation.

A valid journey must have a known zone and valid time. The fare cannot be negative, and the card must have enough balance to leave at least Rs 50 after payment. Peak time is 8:00 AM to before 10:00 AM and 5:00 PM to before 8:00 PM. So, 10:00 AM and 8:00 PM are off-peak.

A procedural program could use variables and separate functions to do the same work. Both designs take O(1) time for one fare calculation and use O(1) memory per card. The main difference is that the object-oriented version keeps related data and functions together, which makes later changes easier.

## Task 2 – Use Tokens, Keywords, Identifiers and Constants Correctly

Keywords are reserved words such as `int`, `class`, `return` and `switch`. Identifiers are names created by the programmer, such as `SmartCard`, `balance` and `calculateFare`. Constants are fixed values. Operators include `+`, `-`, `*`, `/` and `==`. Punctuators include braces, brackets, commas and semicolons.

I would use `constexpr` for values known at compile time, such as fares and the surcharge percentage. Unlike `#define`, it has a type and follows normal C++ scope rules. `const` is useful for values that should not change after initialization. An `enum class` is suitable for zones because it keeps the zone names separate from ordinary integers.

```cpp
enum class Zone { Inner, Middle, Outer };
constexpr long long BASE_FARE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;
```

Class names can use PascalCase, while function and variable names can use camelCase. Names should explain what they represent. Macros do not have normal C++ types or scope. Compile-time constants usually do not need separate runtime storage, and neither choice changes the O(1) fare calculation time.

## Task 3 – Choose Data Types and Check Type Compatibility

Money should be stored as integer paise instead of double rupees. For example, Rs 10.50 is stored as 1050 paise. This avoids floating-point rounding differences when fares are added or deducted. Card balances and network totals should use `long long` because the number of journeys can become large.

| Value | Type | Reason |
|---|---|---|
| Fare and balance | `long long` (paise) | Exact whole-number money values and large totals |
| Peak/concession flag | `bool` | True or false |
| Zone | `enum class Zone` | Only the allowed zones |
| Hour | `int` | Whole hour from 0 to 23 |
| Journey count | `long long` | Large network counts |
| Station code | `char` or `string` | Depends on code format |

On a typical 64-bit g++ system, `bool` and `char` are 1 byte, `int` is 4 bytes, and `long long` and `double` are 8 bytes. These sizes can be checked using `sizeof` on the system used.

When int, double and bool appear in one expression, C++ applies its promotion and conversion rules. An int may be converted to double during arithmetic, and a non-zero integer becomes true when stored in bool. For three million journeys costing Rs 30 each, the total is Rs 90,000,000, or 9,000,000,000 paise. That paise total does not fit in a signed 32-bit int, so long long is safer.

Double rupees also normally uses 8 bytes and addition is O(1), but binary floating point cannot represent every decimal fraction exactly. Integer paise keeps the result exact as long as the integer type does not overflow.

## Task 4 – Control Implicit Conversions

An implicit conversion happens when C++ changes a value to another type automatically. For example, assigning an int expression to double converts the result to double, but it does not bring back any fraction lost during integer division. A char is promoted to int in arithmetic, and a non-zero integer becomes true when assigned to bool.

Brace initialization helps catch narrowing conversions. For example, `int value{3.7};` is rejected because the decimal part would be lost. `static_cast` is useful when a conversion is intentional and should be clear in the code.

For the program in the question, the output is:

```text
3 3.5
C 68
1 true
s >= u
```

The first result is 3 because `a / b` performs integer division before the answer is assigned to double. The explicit cast makes the second division floating point and gives 3.5. The character expression prints C, and then 68 because the character is promoted to its integer code before adding 1. The value 5 converts to true, displayed as 1 first and as true after `boolalpha`. In the signed/unsigned comparison, -1 is converted to a large unsigned value, so the condition is false and the program prints `s >= u`.

Using explicit casts and brace initialization makes conversions clearer and catches some mistakes during compilation. It does not change the O(1) time or storage used for these values.

## Task 5 – Write Correct Expressions with the Right Precedence

The peak-hour check should be:

```cpp
(hour >= 8 && hour < 10) || (hour >= 17 && hour < 20)
```

The parentheses make the two time periods easier to understand. The surcharge can be calculated with `fare += fare * 20 / 100;`. A concession can be applied in a similar way after checking the passenger type.

With `x++`, the current value is used before incrementing. With `++x`, the increment happens first. It is better not to write `i = i++` because the expression is confusing and can cause unsequenced behaviour. Integer division with negative values truncates towards zero, and the remainder has the sign of the left operand.

For the given program, the output is:

```text
11 16
9 6 4
6 4
3 1 -3 -1
18
```

Multiplication happens before addition, so the first line is 11 and 16. In the second line, `x++` uses 5 and then changes x to 6, while `++y` changes y to 4 before using it. Therefore z is 9. The conditional operator prints the larger value, 6. The expression `x % 4 * 2` is evaluated from left to right for these operators and gives 4. The division and remainder results are 3, 1, -3 and -1. The loop adds 0, 3, 6 and 9, giving 18.

A lookup table with 24 bool values could also store which hours are peak. Both approaches take O(1) time to check. The table uses additional space, while the expression does not need a separate table.

## Task 6 – Design the Control Structures

I would use a switch statement to select the base fare for a zone, and if statements to check peak time and the card balance. A range-based for loop is suitable when journeys are stored in an array or container. `continue` can skip an invalid journey, and `break` can stop processing.

Pseudocode:

1. Read the zone, hour and card balance.
2. Select the base fare using the zone.
3. Check whether the hour is in either peak period.
4. If it is peak, add the 20% surcharge.
5. Check whether balance minus fare is at least 5000 paise.
6. If yes, deduct the fare and print the new balance. Otherwise, deny the journey.

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

For the supplied journeys, the fares are Rs 10.00 and Rs 36.00. The third journey is denied because paying Rs 20 would leave less than Rs 50. The balance after the first two journeys is Rs 54.

A fare array indexed by zone is another O(1) option. It uses a small amount of memory and can be convenient when adding zones. With a fourth zone, the enum and the fare array or switch statement must be updated.

## Task 7 – From Procedural to Object-Oriented

In a procedural version, the balance is stored in a variable and separate functions check and deduct the fare. In the object-oriented version, SmartCard keeps the balance private and provides `canTravel()` and `deduct()` functions. This makes it harder for another part of the program to set an invalid balance.

```cpp
class SmartCard {
private:
    long long balancePaise;
    static constexpr long long minimumPaise = 5000;

public:
    explicit SmartCard(long long openingBalance)
        : balancePaise(openingBalance) {}

    bool canTravel(long long farePaise) const {
        return farePaise >= 0 &&
               balancePaise - farePaise >= minimumPaise;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }

    long long balance() const { return balancePaise; }
};
```

Both versions take O(1) time for a balance check or deduction and use O(1) memory per card. If the balance were public, any part of the program could change it without checking the Rs 50 rule. Keeping it private makes the rule easier to protect.

## Task 8 – Read and Print Data Safely

The program should check whether input was read correctly. If letters are entered where a number is expected, cin enters a failed state. The program can use `cin.clear()` to reset the state and `cin.ignore()` to discard the invalid input before asking again. Money can be displayed with `fixed` and `setprecision(2)`.

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
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\\n');
    }

    double rupees = 10.5;
    std::cout << "Fare: Rs " << std::fixed
              << std::setprecision(2) << rupees << '\\n';
}
```

Another option is to read a whole line with `getline()` and convert it using `stoi()` inside try/catch. Both approaches take O(L) time for a line of length L. getline gives more control over the full line, while cin is convenient for simple numeric input.

## Task 9 – Implement and Test the Fare Logic

The fare calculation should be checked for all three zones during peak and off-peak hours. The boundary times matter: 8:00 and 17:00 are peak, while 10:00 and 20:00 are off-peak. A journey should be allowed when the balance after payment is exactly Rs 50, and denied when it would be lower.

| Test | Expected result |
|---|---|
| Inner, off-peak | Rs 10.00 |
| Middle, off-peak | Rs 20.00 |
| Outer, off-peak | Rs 30.00 |
| Inner at 08:00 | Rs 12.00 |
| Outer at 17:00 | Rs 36.00 |
| At 10:00 or 20:00 | No peak surcharge |
| Balance exactly fare + Rs 50 | Allowed |
| Balance below fare + Rs 50 | Denied |
| Unknown zone or negative recharge | Reject input |
| Letters entered for hour | Show error and request input again |

A table-driven test can store the inputs and expected results, then check each row in a loop. Running t test cases takes O(t) time and the table uses O(t) space. Adding another boundary case only needs another row.

## Task 10 – Compare Expectations with Execution

The total should be accumulated in integer paise using long long. If 3,000,000 journeys each cost Rs 30, the total is Rs 90,000,000, or 9,000,000,000 paise. The paise total is greater than the maximum value of a signed 32-bit int, so int is not suitable for this network total. long long can store it safely.

Double can show a decimal total that looks correct for many inputs, but repeated floating-point additions can introduce small differences. Integer paise gives an exact result as long as the total stays within the range of long long. Addition takes O(1) time for these types; the main differences are range and precision.

## Task 11 – Recommend and Defend the Final Design

I would keep the fare values in one constexpr table, use enum class for zones, and store money as long long paise. SmartCard should keep its balance private and provide functions to check and deduct fares. A separate fare calculation function should handle base fares and the peak surcharge. Passenger details can be kept separate so that concession rules do not get mixed into the card balance logic.

This design can handle a large network because each fare calculation and balance update takes O(1) time. If fares change frequently, they could be read from a configuration file at program start. Reading z fare values takes O(z) startup time and O(z) storage, but the program would need to check that the file contains valid values.

## Task 12 – Re-evaluate and Adapt the Design

The new requirements add an Airport zone costing Rs 60, a 10% weekend discount that cannot be combined with the peak surcharge, and a monthly pass that allows unlimited journeys in two selected zones.

I would modify the existing design instead of replacing everything. The fare table can be extended with the Airport fare. A separate Pass class can store the two zones covered by the monthly pass. Before charging the smart card, the program checks whether the pass covers that journey. If it does not, the normal fare is calculated. The weekend discount is applied instead of the peak surcharge, so both adjustments are never applied together.

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
    bool covers(Zone z) const {
        return z == first || z == second;
    }
};
```

For example, an Airport journey normally costs Rs 60. During peak hours on a weekday it costs Rs 72. On a weekend it costs Rs 54, even when the journey is during peak hours, because the weekend discount does not combine with the surcharge. A pass covering the Airport zone makes that covered journey free under the stated unlimited-journey rule.

The brief does not say whether a pass journey must still leave Rs 50 in the stored-value card. That detail should be confirmed before completing the final gate implementation. Overall, the fare table and separate pass logic make the updated requirements easier to handle without changing the whole design.
