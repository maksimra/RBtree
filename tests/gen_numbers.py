from random import randint, choice

key_number = 500
test_number = int(input("Enter tests number:\n"))
max_number = int(input("Enter max number:\n"))

for i in range(1, 1 + test_number):
    test_file = open(f"test_files/{i}keys.txt", "w")
    for j in range(key_number):
        key = randint(1, max_number)
        test_file.write(f"{key} ")
