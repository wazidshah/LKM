#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

#define SUCCESS 0
#define DEVICE_NAME "charDevice"


static int majorNumber;
static int deviceOpen=0;
static char msgBuf[80];
static char *msgPtr;

/*functions defination*/
static int device_open(struct inode* inode,struct file* file)
{
        static int counter = 0;
        
        if(deviceOpen)
        {
                return -EBUSY;
        }
                    
        deviceOpen++;        
        sprintf(msgBuf,"Hello %d\n",counter++);
        msgPtr = msgBuf;
        try_module_get(THIS_MODULE);   
        return SUCCESS;
}


static int device_release(struct inode* inode, struct file* file)
{
        deviceOpen--;
        module_put(THIS_MODULE);
        return 0;
}

static ssize_t device_read(struct file* filp, char* buffer,size_t length, loff_t* offset)
{
        int bytes_read=0;
        
        if(*msgPtr==0)
        {
                return 0;
        }
        
        while(length && *msgPtr)
        {
                put_user(*(msgPtr++),buffer++);
                
                length--;
                bytes_read++;
        }
        return bytes_read;
}

static ssize_t device_write (struct file* filp, const char *buff, size_t len, loff_t *off)
{
        printk(KERN_ALERT "CANNOT WRITE TO THE FILE");
        return -EINVAL;
}

/*End of function definations*/
static struct file_operations fops = 
{
        .read=device_read,
        .write=device_write,
        .open=device_open,
        .release=device_release
};


int init_module(void)
{
        majorNumber = register_chrdev(0,DEVICE_NAME,&fops);
        
        if(majorNumber<0)
        {
                printk(KERN_ALERT "Registration of chardev failed major %d",majorNumber);
                return majorNumber;
        }
         printk(KERN_INFO "SUCCESS!! major %d\n",majorNumber);
         printk(KERN_INFO "Now run mknod /dev/%s c %d 0",DEVICE_NAME,majorNumber);
         return SUCCESS;
}

void cleanup_module(void)
{
       unregister_chrdev(majorNumber,DEVICE_NAME);
        
      /*  if(ret<0)
        {
                 printk(KERN_ALERT "De-registration of chardev failed major %d",majorNumber);
        }*/
}







