#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>

static int value __initdata = 0;
char* str = ""; 
module_param(value,int,S_IRUSR | S_IWUSR);
static char strVal[12] = "";
module_param_string(strVal,strVal,12,S_IRUSR | S_IWUSR);


static int __init withParamInit(void)
{
        if(value==0)
        {
                str="not initialzed during loading";
                printk(KERN_INFO "Initialization and variable:%s",str);
        }
        else
        {
                printk(KERN_INFO "Initialization and variable:%d  strVal:%s",value,strVal);
        }
        
        return 0;
}

static void __exit withParamExit(void)
{
        printk(KERN_INFO "EXITING");
}

module_init(withParamInit);
module_exit(withParamExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wazid Shah");
MODULE_DESCRIPTION("ONLY PRINTS IN KERNEL LOGS DURING INIT AND EXIT");
