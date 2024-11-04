from random import randint, choice

requests_number = 100
tests_number = int(input("Enter tests number:\n"))
max_number = int(input("Enter max number:\n"))

for i in range(1, 1 + tests_number):
    test_file = open(f"test_files/{i}test.txt", "w")
    generated_keys = set()
    for j in range(requests_number):
        if choice(['q', 'k']) == 'k' or j == 0:
            while True:
                key = randint(1, max_number)
                if key not in generated_keys:
                    generated_keys.add(key)
                    test_file.write(f"k {key} ")
                    break
        else:
            value1 = randint(1, max_number)
            value2 = randint(1, max_number)
            test_file.write(f"q {value1} {value2} ")
    test_file.close()
