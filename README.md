# Hackerrank C++ Question Local Runner 

This project allows you to **run and test multiple C++ competition problems locally**, using a structured test case folder setup. Each problem can have multiple test cases, and you can see the input, expected output, and your output for every test case.

---

## Features

* Supports **multiple problems** (q1, q2, etc.) in the same project.
* Each problem has its own `main.cpp` and `testcases/` folder.
* Test cases are organized into separate folders (`case1`, `case2`, ...), each containing `inputX.txt` and `outputX.txt`.
* Runner displays **input, expected output, your output**, and **PASS/FAIL** for each test case.
* Easily extendable by adding new problems or test cases.
* Includes `create_problem.py` to automatically generate problem folders with sample test cases.

---

## Folder Structure

```
project_root/
 ├── create_problem.py       # script to create new problem folders
 ├── run_tests.py            # script to run test cases
 ├── q1/                     # problem 1
 │    ├── main.cpp           # solution for problem 1
 │    └── testcases/
 │         ├── case1/
 │         │    ├── input1.txt
 │         │    └── output1.txt
 │         └── case2/
 │              ├── input2.txt
 │              └── output2.txt
 └── q2/                     # problem 2
      ├── main.cpp
      └── testcases/
           └── ...
```

---

## Usage

### 1. Create a new problem

```bash
python3 create_problem.py
```

* Enter the problem name (e.g., `q1`).
* The script will generate:

  * `main.cpp` for your solution
  * `testcases/` folder with default case folders `case1` and `case2`
  * `inputX.txt` and `outputX.txt` files in each case folder

### 2. Add test cases

* Edit `inputX.txt` with sample input.
* Edit `outputX.txt` with expected output.
* Add more `caseX` folders for additional test cases if needed.

### 3. Run tests

```bash
python3 run_tests.py
```

* The script will list all available problems.
* Select a problem to test.
* It will compile `main.cpp` and run all test cases.
* For each test case, it displays:

  * Input
  * Expected Output
  * Your Output
  * Result: PASS/FAIL

---

## Requirements

* C++17 or higher (g++)
* Python 3

---

## Notes

* Works with any C++ program that reads from standard input and writes to standard output.
* Organizing test cases in separate folders keeps things clean and scalable for competitions.
* You can easily add more problems without modifying the runner script.
* Supports unlimited test cases per problem.

---

This setup is perfect for **coding competitions**, **practice**, or **HackerRank/LeetCode-style local testing**.
