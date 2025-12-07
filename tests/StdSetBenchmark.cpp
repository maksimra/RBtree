#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "getting_value.hpp"

TEST(StdSet, Benchmark)
{
    double time = 0;

    std::set<int> set;
    char key_symbol = 0;
    int value1 = 0, value2 = 0;
    int key = 0;

    while (std::cin >> key_symbol)
    {
        switch (key_symbol)
        {
        case 'k': {
            get_smth_from_istream(&key, std::cin);

            //-bench-start-----------------------
            auto start{std::chrono::steady_clock::now()};

            set.insert(key);

            auto end{std::chrono::steady_clock::now()};
            std::chrono::duration<double> elapsed_seconds{end - start};
            time += elapsed_seconds.count();
            //-bench-end-------------------------
            break;
        }
        case 'q': {
            get_smth_from_istream(&value1, std::cin);
            get_smth_from_istream(&value2, std::cin);

            if (value1 > value2)
            {
                break;
            }

            //-bench-start-----------------------
            auto start{std::chrono::steady_clock::now()};

            auto low = set.lower_bound(value1);
            auto up = set.upper_bound(value2);
            int number_keys = distance(low, up);

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
    std::cout << "std::set time " << time << std::endl;
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}