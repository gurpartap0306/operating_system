#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>

int simple_init(void){
  /*print the value of GOLDEN_RATIO_PRIME*/
  printk(KERN_INFO "%llu\n",GOLDEN_RATIO_PRIME);

  /*print the greatest commit divisor of two numbers*/
  printk(KERN_INFO "%lu\n",gcd(3300,24));

  printk(KERN_INFO "%u\n",HZ);

  printk(KERN_INFO "%lu\n",jiffies);
  return 0;
}

void simple_exit(void){
  printk(KERN_INFO "Removing kernel module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
