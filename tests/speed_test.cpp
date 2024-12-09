#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <set>
#include <climits>
#include <chrono>
#include "../include/compare.hpp"
#include "../include/tree.hpp"
#include "../include/getting_value.hpp"

template <typename Comp>
void RBtree_speed_test (std::fstream& test_file, Comp compare)
{
    Trees::SearchTree<int, Comp> tree (compare);
    int value1 = 0, value2 = 0;
    char key_symbol = 0;
    int key = 0;

    while (test_file >> key_symbol)
    {
        switch (key_symbol)
        {
            case 'k':
                get_smth_from_istream (&key, test_file);
                tree.insert (key);
                break;
            case 'q':
            {
                get_smth_from_istream (&value1, test_file);
                get_smth_from_istream (&value2, test_file);

                Trees::Node<int>* low = tree.lower_bound (value1);
                Trees::Node<int>* up  = tree.upper_bound (value2);

                int number_keys = tree.distance (low, up) + 1;

                break;
            }
            default:
                std::cerr << "Input error" << std::endl;
        }
    }
}

void set_speed_test (std::fstream& test_file)
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
                get_smth_from_istream (&key, test_file);
                set.insert (key);
                break;
            case 'q':
            {
                get_smth_from_istream (&value1, test_file);
                get_smth_from_istream (&value2, test_file);

                auto low = set.lower_bound(value1);
                auto up  = set.upper_bound(value2);

                int number_keys = distance (low, up) + 1;

                break;
            }
            default:
                std::cerr << "Input error" << std::endl;
        }
    }

}

TEST (EndToEnd, CheckNumberKeys)
{
    const int number_tests = 10;

    for (int test_number = 1; test_number <= number_tests; ++test_number)
    {
        std::cout << test_number << " Test" << std::endl;

        std::string test_file_name = "tests/test_files/" + std::to_string (test_number) + "test.txt";
        std::fstream test_file (test_file_name);
        if (!test_file.is_open ())
        {
            throw std::runtime_error ("Failed to open file " + std::string (test_file_name));
        }

        auto start {std::chrono::steady_clock::now()};
        RBtree_speed_test (test_file, compare_int);
        auto end {std::chrono::steady_clock::now()};
        std::chrono::duration<double> elapsed_seconds {end - start};
        std::cout << "my tree time = " << elapsed_seconds.count() << std::endl;

        test_file.clear();
        test_file.seekg(0, std::ios::beg);

        start = std::chrono::steady_clock::now();
        set_speed_test (test_file);
        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << "std::set time = " << elapsed_seconds.count() << std::endl;

        test_file.close ();
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
