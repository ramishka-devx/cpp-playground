import subprocess
import os

PROBLEMS_DIR = "problems"  # all problem folders are now inside problems/
EXEC_FILE = "a.out"

# List all question folders
problems = [d for d in os.listdir(PROBLEMS_DIR) if os.path.isdir(os.path.join(PROBLEMS_DIR, d))]
problems.sort()

print("Available problems:")
for idx, prob in enumerate(problems, start=1):
    print(f"{idx}. {prob}")

choice = input(f"Select a problem to test (1-{len(problems)}): ").strip()
if not choice.isdigit() or not (1 <= int(choice) <= len(problems)):
    print("Invalid selection.")
    exit(1)

problem = problems[int(choice)-1]
problem_path = os.path.join(PROBLEMS_DIR, problem)
cpp_file = os.path.join(problem_path, "main.cpp")
testcases_path = os.path.join(problem_path, "testcases")

if not os.path.exists(cpp_file):
    print(f"{cpp_file} not found!")
    exit(1)

# Compile
print(f"\nCompiling {cpp_file}...")
compile_result = subprocess.run(["g++", "-std=c++17", cpp_file, "-o", EXEC_FILE])
if compile_result.returncode != 0:
    print("Compilation failed.")
    exit(1)

# Find all case folders
cases = sorted([d for d in os.listdir(testcases_path) if os.path.isdir(os.path.join(testcases_path, d))])
if not cases:
    print("No test cases found!")
    exit(1)

passed = 0

for case in cases:
    case_folder = os.path.join(testcases_path, case)
    input_files = sorted([f for f in os.listdir(case_folder) if f.startswith("input")])

    for infile in input_files:
        case_num = infile.replace("input", "").replace(".txt", "")
        output_file = f"output{case_num}.txt"
        input_path = os.path.join(case_folder, infile)
        output_path = os.path.join(case_folder, output_file)

        if not os.path.exists(output_path):
            print(f"Expected output file {output_file} not found in {case_folder}. Skipping.")
            continue

        with open(input_path, "r") as f_in, open(output_path, "r") as f_out:
            expected = f_out.read().strip()
            f_in.seek(0)
            result = subprocess.run(
                [f"./{EXEC_FILE}"],
                stdin=f_in,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            actual = result.stdout.strip()

            # Displaying results with improved readability
            print(f"\n{'-'*40}")
            print(f"--- {case} Test Case {case_num} ---")
            print(f"{'-'*40}")
            print(f"Input:")
            with open(input_path) as f: print(f.read().strip())
            print(f"\n{'-'*40}")
            print(f"Expected Output:")
            print(expected)
            print(f"\n{'-'*40}")
            print(f"Your Output:")
            print(actual)
            print(f"{'-'*40}")
            if actual == expected:
                print("Result: PASS ✅")
                passed += 1
            else:
                print("Result: FAIL ❌")

print(f"\n{passed} test cases passed for {problem}.")
