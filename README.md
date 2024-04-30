# verify_code
this repository just for verify some code query

# [c_windows]  
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
注意:传入函数的是形参，形参本身是绝对无法改变的。
    只有一种特例，形参是地址，通过这个地址解引用去访问值，
    从而改变值，但这种方式同样无法改变地址，因为这个地址是形参。
## is_pointer
验证不同类型指针存放的地址长度是否相同。
验证指针的类型名的作用。
验证结构体大小。
sizeof函数返回值单位为字节。
## is_pointer_addr.c
主要验证和理解任何变量和malloc都是在内存中开辟了一块空间，指针只是指向了这块空间，