#include <linux/module.h>
#include <linux/fs.h>

#define TEST_FILE_PATH  "/home/user/test.txt"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex L.");

struct file * test_file = NULL;
char str[128] = {0};
loff_t temp = 0;

static int __init hello_init(void)
{
    printk(KERN_ALERT "'task4' module started\n");

    test_file = filp_open(TEST_FILE_PATH, O_WRONLY | O_CREAT, 0666);
    if(IS_ERR(test_file)){
        printk(KERN_ALERT "'task4' Error open file!\n");
        return 0;
    }else{
        printk(KERN_ALERT "'task4' Open file!\n");
    }

    sprintf(str, "%s\n", "Hello world!");
    kernel_write(test_file, str, strlen(str), &temp);

    filp_close(test_file, NULL);
    printk(KERN_ALERT "'task4' Close file!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "'task4' module exited\n");
    return;
}

module_init(hello_init);
module_exit(hello_exit);

