#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>

int param=0;

module_param(param,int,S_IRUSR|S_IWUSR);

int init_module1(void)
{
	printk(KERN_INFO "welcome... \n param = %d",param);
return 0;
}

void exit_module1(void)
{
	param = 0;
	printk(KERN_INFO "Bye....\n param = %d",param);

}

module_init(init_module1);
module_exit(exit_module1);
