#include "compare_types.hpp"

int compare_int(int value1, int value2)
{
    return (value1 > value2) - (value1 < value2);
}
