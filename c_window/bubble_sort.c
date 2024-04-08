#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIST_DBG(fmt, ...)      {printf("func:%s ", __func__); \
                                printf("line:%d ",__LINE__); \
                                printf(fmt,##__VA_ARGS__); \
                                }while(0)

#define ARRAY_NUM 10

void bubble_sort(int arrays[], int len);
void swapEle(int array[], int i, int j);

int main()
{
    int array[ARRAY_NUM] = { 0 };
    int i = 0;
    srand(time(NULL));

    for ( i = 0; i < ARRAY_NUM; i++)
    {
        array[i] = rand()%100;
        LIST_DBG("array[%d] = %d\n", i, array[i]);
    }
    
    bubble_sort(array,sizeof(array)/sizeof(array[0]));
    LIST_DBG("after bubble sort\n\n");
    
    for ( i = 0; i < ARRAY_NUM; i++)
    {
        LIST_DBG("array[%d] = %d\n", i, array[i]);
    }
    return 0;
}

void bubble_sort(int arrays[], int len)
{
    int temp = 0;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if ( arrays[j] > arrays[j+1])
            {
               swapEle(arrays, j, j + 1);
            }
        }
    }
}

void swapEle(int array[], int i, int j) 
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}