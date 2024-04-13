#include<stdio.h>

/* 
编译器：MinGW
语言：c
系统：windows11
作用：验证函数名是否是函数地址和对函数名取地址得到的地址是什么
结论：hello与&hello是一样的，函数名是函数地址。
 */

void hello(void)
{
    printf("test\n");
}

int main(int argc,char *argv)
{
    void *name_A, *name_B = NULL;
    
    name_A = hello;
    name_B = &hello;

    printf("hello=%p &hello==%p", hello, &hello);
    return 0;
}