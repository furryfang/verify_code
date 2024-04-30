#include<stdio.h>

/* 
编译器：MinGW
语言：c
系统：windows11
作用：验证不同类型指针存放的地址长度是否相同。
结论：地址的长度只和cpu类型有关，32位处理器地址长度为32位(4字节)，64位处理器同理。
注意：1. 指针存放的只是一段空间的首地址.
    2. 指针的类型决定了++时越过多长字节空间(char加1字节空间)，
    3. 也决定了如何对这段空间解引用。所以不同类型的指针强制转换若类型所占空间不同则会导致解引用时丢掉数据。
    4. 传入函数的是形参，形参本身是绝对无法改变的。只有一种特例，形参是地址，通过这个地址解引用去访问值，
        从而改变值，但这种方式同样无法改变地址，因为这个地址是形参。
 */

#define FURRY_DBG(fmt, ...)      {printf("func:%s ", __func__); \
                                printf("line:%d ",__LINE__); \
                                printf(fmt,##__VA_ARGS__); \
                                }while(0)

/* 
测试不同类型指针存的地址长度是否相同 
结论：相同
*/
void check_point_addr_len(void)
{
    char chr = 'a';
    char *pchr = &chr;
    int value = 10;
    int *pvalue = &value;
    FURRY_DBG("\n&chr=   %p \n&value= %p\n", pchr, pvalue);
}

/* 
测试不同类型指针类型名的作用
结论：指针类型名的作用是确认解引用时访问的内存范围.
    也用来确认对指针++时增加的步长.
*/
void check_point_name(void)
{
    int value = 0x12345678;
    char *chr = NULL;

    chr = &value;
    *chr = 0;
    FURRY_DBG("value = %x\n", value);
}

/*
确认结构体的大小

*/
struct human
{
    int age;
    char weight;
};
//占用空间最大的成员是name(8字节)
//故用8字节大小的框去框man结构体。
// |    8    |    8    |    8    |    8    |
// |    5    |    4    |    8    |    4    |
//man结构体所占空间为32字节
struct man
{
    struct human base;
    int rich;
    char name[8];
    long long work_age;
};

void check_struct_size(void)
{
    FURRY_DBG("struct man size=%d\n", sizeof(struct man));
}


int main(int argc,char *argv)
{
    check_point_addr_len();

    check_point_name();
    check_struct_size();
    FURRY_DBG("long long size=%d\n", sizeof(char));
}