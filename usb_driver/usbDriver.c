#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>




static struct usb_device_id pen_table[]={

{USB_DEVICE(0X1058,0X0820)},
{}
};

MODULE_DEVICE_TABLE (usb, pen_table);

static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "Pen drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
	return 0;
}

static void pen_disconnect(struct usb_interface *interface)
{
	printk(KERN_INFO "My Pendrive is disconnected\n");

}


static struct usb_driver pen_driver = 
{
	.name = "MY USB",
	.id_table = pen_table,
	.probe = pen_probe,
	.disconnect = pen_disconnect,
};

static int __init pen_init(void)
{
	int ret = -1;
	printk(KERN_INFO "Registering driver with kernel\n");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "Registration is completed\n");
	return ret;
}

static void __exit pen_exit(void)
{
	printk(KERN_INFO "De-registering driver with kernel\n");
	usb_deregister(&pen_driver);
	printk(KERN_INFO "De-registration is completed\n");
}


module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WAZID SHAH");
