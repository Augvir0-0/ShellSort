#ifndef MY_SORT_H
#define MY_SORT_H
#include <iostream>
using namespace std;

extern long long compareCount;
extern long long assignCount;

//希尔排序 
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

// Hibbard 增量优化版：gap = 2^k - 1
// 相邻 gap 互质，避免重复比较，时间复杂度 O(n^1.5)
template <typename T> void ShellSort_Hibbard(T *a, int size)
{
    int gaps[30], gcnt = 0;
    for(int k = 1; k <= 30; k++)
    {
        int g = (1 << k) - 1;
        if(g >= size) break;
        gaps[gcnt++] = g;
    }

    for(int g = gcnt - 1; g >= 0; g--)
    {
        int gap = gaps[g];
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

// Sedgewick 增量优化版
// 目前理论最优增量序列，时间复杂度 O(n^1.33)
template <typename T> void ShellSort_Sedgewick(T *a, int size)
{
    int gaps[30], gcnt = 0;
    gaps[gcnt++] = 1;

    for(int k = 1; gcnt < 30; k++)
    {
        int g1 = (1 << (2*k)) + 3 * (1 << (k-1)) + 1;
        if(g1 >= size) break;
        gaps[gcnt++] = g1;

        int g2 = (1 << (2*k+2)) - 3 * (1 << k) + 1;
        if(g2 >= size) break;
        gaps[gcnt++] = g2;
    }

    for(int i = 0; i < gcnt - 1; i++)
        for(int j = 0; j < gcnt - 1 - i; j++)
            if(gaps[j] < gaps[j+1])
            {
                int t = gaps[j];
                gaps[j] = gaps[j+1];
                gaps[j+1] = t;
            }

    for(int g = 0; g < gcnt; g++)
    {
        int gap = gaps[g];
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
