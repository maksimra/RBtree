#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "tree.hpp"
#include "getting_value.hpp"
#include "compare_types.hpp"

TEST(RBtree, Benchmark)
{
    double time = 0;

    Trees::SearchTree<int, int (*)(int, int)> tree(compare_int);
    int value1 = 0, value2 = 0;
    char key_symbol = 0;
    int key = 0;
    while (std::cin >> key_symbol)
    {
        switch (key_symbol)
        {
        case 'k': {
            get_smth_from_istream(&key, std::cin);

            //-bench-start-----------------------
            auto start{std::chrono::steady_clock::now()};

            tree.insert(key);

            auto end{std::chrono::steady_clock::now()};
            std::chrono::duration<double> elapsed_seconds{end - start};
            time += elapsed_seconds.count();
            //-bench-end-------------------------
            break;
        }
        case 'q': {
            get_smth_from_istream(&value1, std::cin);
            get_smth_from_istream(&value2, std::cin);

            //-bench-start-----------------------
            auto start{std::chrono::steady_clock::now()};

            Trees::Node<int> *low = tree.lower_bound(value1);
            Trees::Node<int> *up = tree.upper_bound(value2);
            int number_keys = tree.distance(low, up) + 1;

            auto end{std::chrono::steady_clock::now()};
            std::chrono::duration<double> elapsed_seconds{end - start};
            time += elapsed_seconds.count();
            //-bench-end-------------------------
            break;
        }
        default:
            std::cerr << "Input error" << std::endl;
        }
        if (std::cin.peek() == '\n')
        {
            break;
        }
    }
    std::cout << "RBTree time: " << time << std::endl;
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}