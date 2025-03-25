# 🧩 Sudoku Solver – PB071 Homework 02

This repository contains a C implementation of a **Sudoku assistant** developed as part of the **PB071 (C Programming)** course. The main goal of the assignment is not to solve all types of Sudoku puzzles, but to implement a logic-based elimination approach to solve **simple, uniquely solvable** puzzles.

---

## 📚 Overview

Sudoku is a logic-based puzzle where the objective is to fill a 9x9 grid with digits from 1 to 9 such that:

- Each row contains all digits exactly once.
- Each column contains all digits exactly once.
- Each of the 9 non-overlapping 3x3 boxes contains all digits exactly once.

This project focuses on **eliminating impossible options** in each cell based on already known values, until a solution is reached or no further progress can be made.

---

## 🛠️ Features

### ✅ Core Functionalities

- **Bitwise Cell Representation**:
  Each cell is represented as a set of 9 bits, where each bit corresponds to a digit (1–9). For example:
  ```
  0000000000000001 // Represents digit 1
  0000000100000000 // Represents digit 9
  ```

- **Sudoku I/O**:
  - `load()`: Reads Sudoku from standard input in two supported formats.
  - `print()`: Displays Sudoku with clearly formatted grid and special characters for unknown (`.`) and invalid (`!`) cells.

- **Validation**:
  - `is_valid()`: Verifies that the current Sudoku grid does not contain conflicts and all cells have at least one possible value.
  - `needs_solving()`: Determines whether there are still cells left to solve.

- **Solving**:
  - `solve()`: Iteratively eliminates impossible values for each cell based on rows, columns, and boxes until no further progress is possible.

### 🧪 Helper Functions

- `eliminate_row()`
- `eliminate_col()`
- `eliminate_box()`

Each of these functions performs elimination for a specific region and returns whether any change occurred.


## 📄 Input Formats

Supports two input formats:

### 1. Compact Raw Format (81 characters):
```
000456789000123456000789123312000967697000845845000312231574000968231000574968000
```

### 2. Pretty Printed Format:
```
+=======+=======+=======+
| . . . | 4 5 6 | 7 8 9 |
| . . . | 1 2 3 | 4 5 6 |
| . . . | 7 8 9 | 1 2 3 |
+=======+=======+=======+
| 3 1 2 | . . . | 9 6 7 |
...
```

---

## 💻 Compilation & Execution

Make sure your implementation compiles with the provided `main.c` using:

```bash
gcc -std=c99 -Wall -Wextra -pedantic -o sudoku main.c sudoku.c
```

Then run:

```bash
./sudoku --load --print --solve --print
```

Use `--help` for a full list of supported command-line arguments.

---

## 📌 Notes

- Input validation is strict. Invalid input formats or inconsistent puzzles will be rejected.
- All Sudoku logic is implemented in `sudoku.c`.
- This project demonstrates efficient use of bitwise operations and structured procedural programming in C.

---

## 📂 File Structure

```
📁 sudoku-solver/
├── sudoku.c          # Core implementation
├── sudoku.h          # Header file with function declarations
├── main.c            # Provided main file for testing
├── README.md         # You're reading it!
```