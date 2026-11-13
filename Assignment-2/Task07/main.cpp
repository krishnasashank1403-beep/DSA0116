#include <iostream>
using namespace std;

// Original implementation: once full, every insertion shifts nine elements.
class OriginalHistory {
    int values[10];
    int count;
public:
    OriginalHistory() : count(0) {}
    void add(int value) {
        if (count < 10) values[count++] = value;
        else {
            for (int i = 0; i < 9; ++i) values[i] = values[i + 1];
            values[9] = value;
        }
    }
    void display() const {
        cout << "Original: ";
        for (int i = 0; i < count; ++i) cout << values[i] << ' ';
        cout << '\n';
    }
};

// Redesigned implementation: overwrite the oldest slot in O(1).
class CircularHistory {
    int values[10];
    int count;
    int nextIndex;
public:
    CircularHistory() : count(0), nextIndex(0) {}
    void add(int value) {
        values[nextIndex] = value;
        nextIndex = (nextIndex + 1) % 10;
        if (count < 10) ++count;
    }
    void display() const {
        cout << "Circular: ";
        int start = count == 10 ? nextIndex : 0;
        for (int i = 0; i < count; ++i)
            cout << values[(start + i) % 10] << ' ';
        cout << '\n';
    }
};
int main() {
    OriginalHistory original;
    CircularHistory redesigned;
    for (int i = 1; i <= 15; ++i) {
        original.add(i);
        redesigned.add(i);
    }
    cout << "Last 10 transactions after inserting 1..15\n";
    original.display();
    redesigned.display();
}