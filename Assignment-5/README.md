# DSA0116 – Assignment 5 (CO5)
## Reliable Software with Runtime Polymorphism and Exceptions

### Task folders
- Task01 – Polymorphic Bill hierarchy and payer implementations
- Task02 – Exception handling, validation, rethrowing and resource cleanup
- Task03 – Runtime measurement of bill processing and error-handling approaches
- Task04 – Extension with a new bill type and payer

Each task folder contains `main.cpp` and `run-output.txt`.

### Compile and run
From each task directory:
```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o main
./main
```

For sanitizer checks:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g main.cpp -o main
./main
```

For timing experiments, compile Task03 with optimization:
```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o main
./main
```

### Important evidence notes
- Task03 reports measurements from the machine on which it is executed; do not copy timing values from another computer.
- The output text files are sample/expected outputs, not screenshots or proof of local execution.
- The PDF also requires Part A design artefacts (UML, vtable diagrams, pseudocode, exception strategy and complexity analysis), plus experimental interpretations and sanitizer evidence. Those report-only deliverables are not replaced by these code folders.
- Task B2's allocation-failure behaviour can differ by standard library and available memory; record the actual exception and message from your own run.

### Compiler
g++ with C++17 support.
