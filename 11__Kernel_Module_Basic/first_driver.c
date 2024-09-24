#include <linux/module.h>   /* macro like module_init/module_exit */
#include <linux/fs.h>       /* function that allocates major/minor number */
#include <linux/device.h>   /* function: class_create/device_create */
#include <linux/cdev.h>     /* kmalloc */
#include <linux/slab.h>     /* cdev_init/cdev_add */
#include <linux/uaccess.h>  /* copy_to_user/copy_from_user */

#define DRIVER_AUTHOR   "Vion vion@gmail.com"
#define DRIVER_DESC     "First kernel module"
#define DRIVER_VERS     "1.0.0"
#define MEM_SIZE        1024

struct my_foo_dev
{
    uint8_t *p_kernel_buffer;
    dev_t dev_num;
    struct class *m_class;
    struct cdev m_cdev;
} mdev;

static int      __init first_driver_init(void);
static void     __exit first_driver_exit(void);
static int      m_open(struct inode *inode, struct file *file);
static int      m_release(struct inode *inode, struct file *file);
static ssize_t  m_read(struct file *filp, char __user *user_buf, size_t size, loff_t * offset);
static ssize_t  m_write(struct file *filp, const char *user_buf, size_t size, loff_t * offset);

static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = m_read,
    .write      = m_write,
    .open       = m_open,
    .release    = m_release,
};

/* Be called when open Device file */
static int m_open(struct inode *inode, struct file *file)
{
    pr_info("System call open() called...!!!\n");
    return 0;
}

/* Be called when close Device file */
static int m_release(struct inode *inode, struct file *file)
{
    pr_info("System call close() called...!!!\n");
    return 0;
}

/* Be called when read Device file */
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset)
{
    size_t to_read;

    pr_info("System call read() called...!!!\n");

    if (*offset >= MEM_SIZE) 
        return 0;

    to_read = ((MEM_SIZE - *offset) > size) ? size : ((size_t)(MEM_SIZE - *offset));
    copy_to_user(user_buf, mdev.p_kernel_buffer + *offset, to_read);

    *offset += to_read;
    printk(KERN_INFO "Data Read : Done!\n");
    
    return to_read;
}

/* Be called when write Device file */
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset)
{
    pr_info("System call write() called...!!!\n");
    copy_from_user(mdev.p_kernel_buffer, user_buf, size);
    printk(KERN_INFO "Data Write : Done!\n");
    return size;
}

/* Constructor */
static int  __init first_driver_init(void)
{
    if (alloc_chrdev_region(&mdev.dev_num, 0, 1, "m_cdev") < 0) // (cat /pro/devices)
    {
        printk(KERN_INFO "Major number allocation is failed\n");
        return -1;
    }
    pr_info("Major = %d & Minor = %d", MAJOR(mdev.dev_num), MINOR(mdev.dev_num));

    /* initialize a cdev structure */
    cdev_init(&mdev.m_cdev, &fops);

    /* add a char device to the system */
    if ((cdev_add(&mdev.m_cdev, mdev.dev_num, 1)) < 0) 
    {
        pr_err("Cannot add the device to the system\n");
        goto rm_device_num;
    }

    if ((mdev.m_class = class_create(THIS_MODULE, "m_class")) == NULL)   // (/sys/class)
    {
        printk(KERN_INFO "Creating class failed\n");
        goto rm_device_num;
    }

    if ((device_create(mdev.m_class, NULL, mdev.dev_num, NULL, "m_device")) == NULL)    // (/dev), remember chmod
    {
        printk(KERN_INFO "Creating device failed\n");
        goto rm_class;
    }

    if ((mdev.p_kernel_buffer = kmalloc(MEM_SIZE, GFP_KERNEL)) == 0)
    {
        printk(KERN_INFO "Cannot allocate memory in kernel\n");
        goto rm_device;
    }

    printk(KERN_INFO "First kernel module hello\n");
    return 0;

rm_device:
    device_destroy(mdev.m_class, mdev.dev_num);
rm_class:
    class_destroy(mdev.m_class);
rm_device_num:
    unregister_chrdev_region(mdev.dev_num, 1);
    return -1;
}

/* Destructor */
static void  __exit first_driver_exit(void)
{
    kfree(mdev.p_kernel_buffer);
    device_destroy(mdev.m_class, mdev.dev_num);
    class_destroy(mdev.m_class);
    unregister_chrdev_region(mdev.dev_num, 1);

    printk(KERN_INFO "Goodbye from first kernel module\n");
}

module_init(first_driver_init);
module_exit(first_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
MODULE_VERSION(DRIVER_VERS);
