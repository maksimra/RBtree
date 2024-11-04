#include <cstdio>
#include <iostream>
#include "../include/tree.hpp"
#include "../include/compare.hpp"
#include "../include/getting_value.hpp"

int main ()
{
    try
    {
        Trees::SearchTree<int, int (*) (int, int)> tree (compare_int);
        int  value1 = 0, value2 = 0;
        char key_symbol = 0;
        int  key = 0;

        while (std::cin >> key_symbol)
        {
            switch (key_symbol)
            {
                case 'k':
                    get_smth_from_istream (&key, std::cin);
                    tree.insert (key);
                    break;
                case 'q':
                {
                    get_smth_from_istream (&value1, std::cin);
                    get_smth_from_istream (&value2, std::cin);

                    Trees::Node<int>* low = tree.lower_bound (value1);
                    Trees::Node<int>* up  = tree.upper_bound (value2);

                    int number_keys = tree.distance (low, up) + 1;
                    if (number_keys <= 0)
                        number_keys = 0;

                    std::cout << number_keys << " ";
                    break;
                }
                default:
                    std::cerr << "Input error" << std::endl;
            }
        }
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what () << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
