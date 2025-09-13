#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <set>
#include <climits>
#include "tree.hpp"
#include "compare.hpp"
#include "getting_value.hpp"

template <typename Comp>
void RBtree_test (std::fstream& test_file, std::vector<size_t>& num_keys_vec, Comp compare)
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

                if (number_keys <= 0)
                    number_keys = 0;

                num_keys_vec.push_back (number_keys);
                break;
            }
            default:
                std::cerr << "Input error" << std::endl;
        }
    }
}

TEST (UnitTest, BoundCheck)
{
    Trees::SearchTree<int, int (*) (int, int)> tree (compare_int);
    tree.insert (25);

    EXPECT_EQ (tree.lower_bound (24)->key, 25);
    EXPECT_EQ (tree.upper_bound (26)->key, 25);
}

TEST (UnitTest, NoThrowTest)
{
    const int number_tests = 5;
    const int number_keys  = 100;

    for (int test_number = 1; test_number <= number_tests; ++test_number)
    {
        Trees::SearchTree<int, int (*)(int, int)> tree1(compare_int);

        std::string test_file_name = "tests/test_files/" + std::to_string (test_number) + "keys.txt";
        std::fstream test_file(test_file_name);
        if (!test_file.is_open())
        {
            throw std::runtime_error("Failed to open file " + std::string (test_file_name));
        }

        int key = 0;
        for (int key_number = 0; key_number < number_keys; ++key_number)
        {
            if (!(test_file >> key))
            {
                throw std::runtime_error("Failed to read key from file " + test_file_name);
            }
            tree1.insert(key);
        }

        Trees::SearchTree<int, int (*)(int, int)> tree2(compare_int);

        ASSERT_NO_THROW(tree2 = tree1);
        Trees::SearchTree<int, int (*)(int, int)> tree3(tree1);
        test_file.close();
    }
}

TEST (EndToEnd, CheckNumberKeys)
{
    const int number_tests = 10;

    std::vector<size_t> num_keys_vec;
    for (int test_number = 1; test_number <= number_tests; ++test_number)
    {
        std::cout << test_number << " Test" << std::endl;

        std::string test_file_name = "tests/test_files/" + std::to_string (test_number) + "test.txt";
        std::fstream test_file (test_file_name);
        if (!test_file.is_open ())
        {
            throw std::runtime_error ("Failed to open file " + std::string (test_file_name));
        }

        std::string answ_file_name = "tests/test_files/" + std::to_string (test_number) + "answ.txt";
        std::fstream answ_file (answ_file_name);
        if (!answ_file.is_open ())
        {
            throw std::runtime_error ("Failed to open file " + std::string (answ_file_name));
        }

        ASSERT_NO_THROW (RBtree_test (test_file, num_keys_vec, compare_int));
        size_t ref_num_keys = SIZE_MAX;
        auto vec_end = num_keys_vec.end ();

        for (auto it = num_keys_vec.begin (); answ_file >> ref_num_keys; ++it)
        {
            if (it == vec_end || *it != ref_num_keys)
            {
                std::cerr << "\n*it and ref_num = " << *it << " " << ref_num_keys << std::endl;
                throw std::runtime_error ("Fail test");
            }
        }

        test_file.close ();
        answ_file.close ();
        num_keys_vec.clear ();
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
