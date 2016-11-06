#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#define AUTHOR "Miao Chiang Yen <claude51315@gmail.com>"
#define DESCRIPTION "hello world!"

static int hello4_data __initdata = 6666;
static int __init hello4_init(void){
    printk(KERN_INFO "hello kernel4  %d!\n", hello4_data);
    return 0;
}
static void __exit hello4_exit(void){
    printk(KERN_INFO "goodbye kernel4!\n");
}

module_init(hello4_init);
module_exit(hello4_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);

