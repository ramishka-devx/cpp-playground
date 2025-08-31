import os

PROBLEMS_DIR = "problems"

def create_problem(problem_name, num_cases=2):
    problem_path = os.path.join(PROBLEMS_DIR, problem_name)
    
    if os.path.exists(problem_path):
        print(f"Problem folder '{problem_name}' already exists!")
        return

    # Ensure problems directory exists
    os.makedirs(PROBLEMS_DIR, exist_ok=True)

    # Create main problem folder
    os.makedirs(problem_path)
    print(f"Created folder: {problem_path}")

    # Create main.cpp file
    main_cpp_path = os.path.join(problem_path, "main.cpp")
    with open(main_cpp_path, "w") as f:
        f.write("""#include <bits/stdc++.h>
using namespace std;

int main() {
    // Your solution here
    return 0;
}
""")
    print(f"Created file: {main_cpp_path}")

    # Create testcases folder
    testcases_path = os.path.join(problem_path, "testcases")
    os.makedirs(testcases_path)
    print(f"Created folder: {testcases_path}")

    # Create test case subfolders
    for i in range(1, num_cases + 1):
        case_folder = os.path.join(testcases_path, f"case{i}")
        os.makedirs(case_folder)
        with open(os.path.join(case_folder, f"input{i}.txt"), "w") as f:
            f.write("")  # empty input
        with open(os.path.join(case_folder, f"output{i}.txt"), "w") as f:
            f.write("")  # empty output
        print(f"Created test case folder: {case_folder} with input{i}.txt and output{i}.txt")

if __name__ == "__main__":
    name = input("Enter problem name (e.g., q1): ").strip()
    create_problem(name)
