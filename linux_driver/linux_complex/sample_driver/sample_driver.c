#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init sample_driver_in(void)
{
    printk("%s\n", __func__);
    return 0;
}

static void __exit sample_driver_out(void)
{
    printk("%s\n", __func__);
}

module_init(sample_driver_in);
module_exit(sample_driver_out);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("sample driver demo");