/*

*/
/* 
编译器：MinGW
语言：c
系统：windows11
作用：主要验证和理解任何变量和malloc都是在内存中开辟了一块空间，指针只是指向了这块空间，
结论：指针的改变只是指向了其他空间，并不会对空间中本身的内容造成改变。
    而解引用后的赋值，是将其他空间的内容拷贝一份一模一样的到当前空间。
注意：
 */
#include<stdio.h>
#include<stdlib.h>

int age_change = 25;
int *page_change = &age_change;
/*
1. 型参为一级指针，通过解引用的方式访问地址指向的空间，从而改变空间中的值。
此为值传递，将age_change空间里的值复制给了age那片空间。
此时内存中存在两块值为25的空间。
*/
void func_value_change(int *orange)
{
    *orange = age_change;
}

void verify_value_change(void)
{
    int *age = malloc(sizeof(int));
    *age = 18;
    printf("age=%d,addr_age=0x%p, age_change=%d, addr_change=0x%p\n", 
            *age, age, age_change, &age_change);
    func_value_change(age);
    printf("age=%d,addr_age=0x%p, age_change=%d, addr_change=0x%p\n", 
            *age, age, age_change, &age_change);
}

/*
2. 型参为二级指针，通过解引用的方式可以访问到一级指针。
此时就可以将一级指针指向其它地址。注意，若一级指针原来指向了一块空间，则会导致内存泄漏。
如下例子就会导致内存泄漏，一级指针重新指向后38行分配的空间就没有指针指向。
*/
void func_addr_change(int **orange)
{
    *orange = page_change;
}
void verify_addr_change(void)
{
    int *age = malloc(sizeof(int));
    int **ppage = &age;
    *age = 18;

    printf("age=%p,age=%d, *ppage=%p,**ppage=%d, age_change=%d, addr_change=0x%p\n", 
            age, *age, *ppage, **ppage, age_change, &age_change);
    func_addr_change(ppage);
    printf("age=%p,age=%d, *ppage=%p,**ppage=%d, age_change=%d, addr_change=0x%p\n", 
            age, *age, *ppage, **ppage, age_change, &age_change);
    printf("");
}

/*
3. 型参为二级指针，但一级指针指向的不是malloc分配的空间。
这样一级指针原来指向的空间会随着函数的结束将空间释放，不会内存泄漏。
*/
void func_loacl_addr_change(int **orange)
{
    *orange = page_change;
}
void verify_loacl_addr_change(void)
{
    int age = 18;
    int *page = &age;
    int **ppage = &page;

    printf("age=%d, *ppage=%p,**ppage=%d, age_change=%d, addr_change=0x%p\n", 
            age, *ppage, **ppage, age_change, &age_change);
    func_addr_change(ppage);
    printf("age=%d, *ppage=%p,**ppage=%d, age_change=%d, addr_change=0x%p\n", 
            age, *ppage, **ppage, age_change, &age_change);
}

int main(int argc, char *argv)
{
//    verify_value_change();
    // verify_addr_change();
    verify_loacl_addr_change();
}
