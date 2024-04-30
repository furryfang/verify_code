# linux驱动

**概述**  
想法是从最简单的驱动结构开始将大部分的驱动形式和调试方法以demo的方式写出来。
深入就是学习各种复杂驱动的实现和使用,类似USB驱动，SDIO驱动等。  
**linux下驱动架构形式**主要是linux的驱动架构及形式，偏向于固定格式。  
**linux下复杂驱动**主要是linux下复杂驱动的使用及实现，同步学习各种复杂通信协议。

## linux下驱动架构形式

1.最简单的驱动
sample_driver.c
主要涉及linux下驱动入口/驱动出口/驱动开源协议/基本的驱动头文件。
驱动加载入口module_init()

```c
#define module_init(x)	__initcall(x);
#define __initcall(fn) device_initcall(fn)
```

然后发现内核中有如下一些加载定义,将驱动在不同时间加载。

```c
#define pure_initcall(fn)		__define_initcall(fn, 0)

#define core_initcall(fn)		__define_initcall(fn, 1)
#define core_initcall_sync(fn)		__define_initcall(fn, 1s)
#define postcore_initcall(fn)		__define_initcall(fn, 2)
#define postcore_initcall_sync(fn)	__define_initcall(fn, 2s)
#define arch_initcall(fn)		__define_initcall(fn, 3)
#define arch_initcall_sync(fn)		__define_initcall(fn, 3s)
#define subsys_initcall(fn)		__define_initcall(fn, 4)
#define subsys_initcall_sync(fn)	__define_initcall(fn, 4s)
#define fs_initcall(fn)			__define_initcall(fn, 5)
#define fs_initcall_sync(fn)		__define_initcall(fn, 5s)
#define rootfs_initcall(fn)		__define_initcall(fn, rootfs)
#define device_initcall(fn)		__define_initcall(fn, 6)
#define device_initcall_sync(fn)	__define_initcall(fn, 6s)
#define late_initcall(fn)		__define_initcall(fn, 7)
#define late_initcall_sync(fn)		__define_initcall(fn, 7s)
```

驱动卸载入口module_exit()

```c
#define module_exit(x)	__exitcall(x);
#define __exitcall(fn)						\
	static exitcall_t __exitcall_##fn __exit_call = fn
```

## linux下复杂驱动
