// source file for the functions header

#include "functions.hpp"
#include <array>


short kroneckerDelta(short i, short j)
{
    if(i == j)
        return 1;
    else
        return 0;
}

bool isEvenPermutation(short i, short j, short k)
{
    if(
        j == (i + 1) % 3 &&
        k == (j + 1) % 3 &&
        i == (k + 1) % 3
        )
        return true;
    else
        return false;    
}

bool isOddPermutation(short i, short j, short k)
{
    if(
        i == (j + 1) % 3 &&
        k == (i + 1) % 3 &&
        j == (k + 1) % 3
        )
        return true;
    else
        return false;
}

short int leviCivita(short i, short j, short k)
{
    if(isEvenPermutation(i, j, k))
        return 1;

    else if(isOddPermutation(i, j, k))
        return -1;
        
    else
        return 0;
}
