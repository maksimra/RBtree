#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include "getting_value.hpp"

void std_set_test(std::fstream &test_file, std::vector<size_t> &num_keys_vec)
{
    std::set<int> set;
    int value1 = 0, value2 = 0;
    char key_symbol = 0;
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
                num_keys_vec.push_back(0);
                break;
            }

            auto low = set.lower_bound(value1);
            auto up = set.upper_bound(value2);

            int number_keys = distance(low, up);
            num_keys_vec.push_back(number_keys);

            break;
        }
        default:
            std::cerr << "Input error" << std::endl;
        }
    }
}

TEST(StdSet, CheckNumberKeys)
{
    const int number_tests = 10;

    std::vector<size_t> num_keys_vec;
    for (int test_number = 1; test_number <= number_tests; ++test_number)
    {
        std::cout << test_number << " Test" << std::endl;

        std::string test_file_name = "tests/test_files/" + std::to_string(test_number) + "test.txt";
        std::fstream test_file(test_file_name);
        if (!test_file.is_open())
        {
            throw std::runtime_error("Failed to open file " + std::string(test_file_name));
        }

        std::string answ_file_name = "tests/test_files/" + std::to_string(test_number) + "answ.txt";
        std::fstream answ_file(answ_file_name);
        if (!answ_file.is_open())
        {
            throw std::runtime_error("Failed to open file " + std::string(answ_file_name));
        }

        ASSERT_NO_THROW(std_set_test(test_file, num_keys_vec));
        size_t ref_num_keys = SIZE_MAX;
        auto vec_end = num_keys_vec.end();

        for (auto it = num_keys_vec.begin(); answ_file >> ref_num_keys; ++it)
        {
            if (it == vec_end || *it != ref_num_keys)
            {
                throw std::runtime_error("Fail test");
            }
        }

        test_file.close();
        answ_file.close();
        num_keys_vec.clear();
    }
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}