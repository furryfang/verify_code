#include<stdio.h>
/* 
编译器：MinGW
语言：c
系统：windows11
作用：一个简单的函数指针及指针函数的使用
结论：函数指针只是一个指向函数的指针，和普通指针并没什么不同。指针函数是返回值为指针的
    函数，注意不能返回局部变量的指针，只能返回全局变量/static修饰的局部变量的指针。
 */

#define LIST_DBG(fmt, ...)      {printf("func:%s ", __func__); \
                                printf("line:%d ",__LINE__); \
                                printf(fmt,##__VA_ARGS__); \
                                }while(0)

/*
这是demo2的结构体，里面有函数指针成员。
*/
struct demo2_s
{
    int (*func_pointer)(int);
    int this_num;
};

void demo1(void);
void demo2_1(struct demo2_s *temp);
void demo2(void);
void demo3(void);
int demo3_1(int num, int (*call_back)(int times));
int demo3_callback(int times);

/*
这是一个测试函数
*/
int print_tool(int num)
{
    LIST_DBG("func num=%d\n", num);
    return num;
}

int main(void)
{
    // demo1();
    // demo2();
    demo3();
    return 0;
}

/*
demo1演示了通过将函数指针指向函数，访问函数指针的方式访问函数。
*/
void demo1(void)
{
    int (*func_pointer)(int);
    func_pointer = &print_tool;
    func_pointer(5);
    func_pointer(7);
}

/*
demo2演示了通过函数指针绑定函数到结构体中，从而传递此结构体即可在任何地方访问函数。
*/
void demo2(void)
{
    struct demo2_s test;
    test.func_pointer = &print_tool;
    test.this_num = 33;

    demo2_1(&test);
}

void demo2_1(struct demo2_s *temp)
{
    temp->func_pointer(temp->this_num);
}

/*
demo3演示了函数指针在回调函数中的使用。
*/
void demo3(void)
{
    int ret = 0;
    ret = demo3_1(17, &demo3_callback);
    LIST_DBG("ret=%d", ret);
}

int demo3_1(int num, int (*call_back)(int times))
{
    LIST_DBG("num=%d\n", num);
    return call_back(num);
}

int demo3_callback(int times)
{
    LIST_DBG("times=%d\n", times);
    return 1;
}