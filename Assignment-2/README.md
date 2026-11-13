# DSA0116 — Assignment 2

Seven standalone C++ solutions for CO2: Functions and Object-Oriented Concepts.

## Repository layout

| Folder | Topic | Files |
|---|---|---|
| `Task01/` | Call by value, reference, pointer, reference return and default arguments | `main.cpp`, `run-output.txt` |
| `Task02/` | Return by reference, const reference, copy and dangling-reference warning | `main.cpp`, `run-output.txt` |
| `Task03/` | Default arguments and function overloading | `main.cpp`, `run-output.txt` |
| `Task04/` | Class with a fixed-size transaction array | `main.cpp`, `run-output.txt` |
| `Task05/` | Static data members and arrays of objects | `main.cpp`, `run-output.txt` |
| `Task06/` | Friend functions and inline functions | `main.cpp`, `run-output.txt` |
| `Task07/` | Shift-based history versus a circular buffer | `main.cpp`, `run-output.txt` |

## Build and run

Compile any task with a C++17 compiler. For example:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic Task01/main.cpp -o task01
./task01
```

Replace `Task01` with the desired folder. On Windows, run the generated executable as `task01.exe`.

## Notes

- Each task is an independent program with its own `main()`.
- Task 2 contains a deliberately unsafe dangling-reference function to demonstrate the compiler warning. The function is not called.
- The `run-output.txt` files contain sample runs from a Linux/g++ environment. Capture your own terminal screenshots and record your own compiler version for submission.
- Timing tables and benchmark evidence must be measured on the machine used for the assignment; no timings are fabricated here.
