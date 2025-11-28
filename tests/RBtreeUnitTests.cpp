#include "compare.hpp"
#include "getting_value.hpp"
#include "tree.hpp"
#include <climits>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <set>

TEST(UnitTest, BoundCheck)
{
    Trees::SearchTree<int, int (*)(int, int)> tree(compare_int);
    tree.insert(25);

    EXPECT_EQ(tree.lower_bound(24)->key, 25);
    EXPECT_EQ(tree.upper_bound(26)->key, 25);
}

TEST(UnitTest, NoThrowTest)
{
    const int number_tests = 5;
    const int number_keys = 100;

    for (int test_number = 1; test_number <= number_tests; ++test_number)
    {
        Trees::SearchTree<int, int (*)(int, int)> tree1(compare_int);

        std::string test_file_name = "tests/test_files/" + std::to_string(test_number) + "keys.txt";
        std::fstream test_file(test_file_name);
        if (!test_file.is_open())
        {
            throw std::runtime_error("Failed to open file " + std::string(test_file_name));
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
        test_file.close();

        Trees::SearchTree<int, int (*)(int, int)> tree2(compare_int);

        ASSERT_NO_THROW(tree2 = tree1);
        Trees::SearchTree<int, int (*)(int, int)> tree3(tree1);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
