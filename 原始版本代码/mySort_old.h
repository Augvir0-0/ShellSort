#ifndef MY_SORT_H
#define MY_SORT_H
#include <iostream>
using namespace std;

extern long long compareCount;
extern long long assignCount;

//Ï£¶ûÅÅÐò 
template <typename T> void ShellSort(T *a, int size)
{
    for(int gap = size/2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < size; i++)
        {
            T temp = a[i];
            assignCount++;
            int j = i;

            while(j >= gap)
            {
                compareCount++;
                if(a[j - gap] > temp)
                {
                    a[j] = a[j - gap];
                    assignCount++;
                    j -= gap;
                }
                else break;
            }

            a[j] = temp;
            assignCount++;
        }
    }
}

template <typename T> bool Check(const T *a, int size)
{
    for(int i = 1; i < size; i++)
        if(a[i-1] > a[i])
            return false;
    return true;
}

#endif
