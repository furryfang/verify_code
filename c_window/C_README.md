# c语言问题及数据结构实现

此文件夹下主要验证记录c语言的各种问题和数据结构的实现

## is_thread_run_when_process_exit.c  

verify that the thread exists when the main process exits  
这个文件验证了在windows64位系统下当进程结束时进程中的线程是否会自动结束。  

## is_func_name_point.c

验证了在c语言中函数名是否是函数地址。  

## module_oneway_list.c  

verify that the list  
一个简单的单向链表，包含创建/删除/增加/弹出 操作。

## bubble_sort  

bubble sort  
c语言实现的冒泡排序。  

## pointer_func

指针函数的使用说明和常用方式。

## is_pointer

验证不同类型指针存放的地址长度是否相同。
验证指针的类型名的作用。
验证结构体大小。
sizeof函数返回值单位为字节。

## is_pointer_addr.c

主要验证和理解任何变量和malloc都是在内存中开辟了一块空间，指针只是指向了这块空间.
