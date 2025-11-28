#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <set>
#include "getting_value.hpp"

void set_speed_test(std::fstream &test_file)
{
    std::set<int> set;
    char key_symbol = 0;
    int value1 = 0, value2 = 0;
    int key = 0;

    while (test_file >> key_symbol)
    {
        switch (key_symbol)
        {
        case 'k':
            get_smth_from_istream(&key, test_file);
            set.insert(key);
            break;
        case 'q': {
            get_smth_from_istream(&value1, test_file);
            get_smth_from_istream(&value2, test_file);

            if (value1 > value2)
            {
                break;
            }

            auto low = set.lower_bound(value1);
            auto up = set.upper_bound(value2);

            int number_keys = distance(low, up);

            break;
        }
        default:
            std::cerr << "Input error" << std::endl;
        }
    }
}

TEST(StdSet, Benchmark)
{
    const int number_tests = 10;

    for (int test_number = 1; test_number <= number_tests; ++test_number)
    {
        std::cout << test_number << " Test" << std::endl;

        std::string test_file_name = "tests/test_files/" + std::to_string(test_number) + "test.txt";
        std::fstream test_file(test_file_name);
        if (!test_file.is_open())
        {
            throw std::runtime_error("Failed to open file " + std::string(test_file_name));
        }

        auto start{std::chrono::steady_clock::now()};
        set_speed_test(test_file);
        auto end{std::chrono::steady_clock::now()};
        std::chrono::duration<double> elapsed_seconds{end - start};
        std::cout << "StdSet time = " << elapsed_seconds.count() << std::endl;

        test_file.close();
    }
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}