// an example kernel module using GPIO with interrupts:


#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/gpio.h>                       // for the GPIO functions 
#include <linux/interrupt.h>                  // for the IRQ code

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Group 1"); 
MODULE_DESCRIPTION("A Button/LED test driver for the RPi"); 
MODULE_VERSION("0.1");

// static unsigned int gpioLED = 17;             // pin 11 (GPIO17) 
// static unsigned int gpioButton = 27;          // pin 13 (GPIO27) 

static unsigned int gpioEncoder = 27;          // pin 13 (GPIO27) 

static unsigned int irqNumber;                // share IRQ num within file 
static unsigned int numberPresses = 0;        // store number of presses 
// static bool         ledOn = 0;                // used to invert state of LED


// prototype for the custom IRQ handler function, function below 
static irq_handler_t  erpi_gpio_irq_handler(unsigned int irq, 
                                            void *dev_id, struct pt_regs *regs);


//Funktion für sysfs zum Auslesen der testiable in UserSpace
static ssize_t number_presses_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%u\n", numberPresses);
}

// erstellt schreibgeschützten sysfs-Eintrag
static struct kobj_attribute number_presses_attribute = __ATTR_RO(number_presses);

static struct kobject *test_kobj;


static int __init erpi_gpio_init(void) 
{
    int result = 0;
    printk(KERN_INFO "GPIO_TEST: Initializing the GPIO_TEST LKM\n");

    // if (!gpio_is_valid(gpioLED)) 
    // {
    //     printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
    //     return -ENODEV;
    // }   

    // ledOn = true;

    // gpio_request(gpioLED, "sysfs");          // request LED GPIO
    // gpio_direction_output(gpioLED, ledOn);   // set in output mode and on 
    // // gpio_set_value(gpioLED, ledOn);       // not reqd - see line above
    // gpio_export(gpioLED, false);             // appears in /sys/class/gpio
    //                                          // false prevents in/out change   
    gpio_request(gpioEncoder, "sysfs");       // set up gpioEncoder   
    gpio_direction_input(gpioEncoder);        // set up as input   
    // gpio_set_debounce(gpioEncoder, 200);      // debounce delay of 200ms
    gpio_export(gpioEncoder, false);          // appears in /sys/class/gpio

    // printk(KERN_INFO "GPIO_TEST: button value is currently: %d\n", 
    //        gpio_get_value(gpioButton));

    irqNumber = gpio_to_irq(gpioEncoder);     // map GPIO to IRQ number
    printk(KERN_INFO "GPIO_TEST: Encoder mapped to IRQ: %d\n", irqNumber);

    // This next call requests an interrupt line   
    result = request_irq(irqNumber,          // interrupt number requested            
        (irq_handler_t) erpi_gpio_irq_handler,   // handler function            
        IRQF_TRIGGER_RISING,                     // on rising edge (press, not release)            
        "erpi_gpio_handler",                     // used in /proc/interrupts
        NULL);                                   // *dev_id for shared interrupt lines
    printk(KERN_INFO "GPIO_TEST: IRQ request result is: %d\n", result);

    // sysfs-Eintrag für numberPresses erstellen
    test_kobj = kobject_create_and_add("test", kernel_kobj);
    if (!test_kobj)
        return -ENOMEM;

    if (sysfs_create_file(test_kobj, &number_presses_attribute.attr)) {
        printk(KERN_ERR "Cannot create sysfs entry\n");
        kobject_put(test_kobj);
        return -ENOMEM;
    }



    return result;
}

static void __exit erpi_gpio_exit(void) 
{   
    // printk(KERN_INFO "GPIO_TEST: button value is currently: %d\n", 
    //        gpio_get_value(gpioButton));

    printk(KERN_INFO "GPIO_TEST: pressed %d times\n", numberPresses);
    // gpio_set_value(gpioLED, 0);              // turn the LED off
    // gpio_unexport(gpioLED);                  // unexport the LED GPIO   
    free_irq(irqNumber, NULL);               // free the IRQ number, no *dev_id   
    gpio_unexport(gpioEncoder);               // unexport the Encoder GPIO   
    // gpio_free(gpioLED);                      // free the LED GPIO
    gpio_free(gpioEncoder);                   // free the Button GPIO
    printk(KERN_INFO "GPIO_TEST: Goodbye from the LKM!\n"); 
}
    // ## Handler Funktion
static irq_handler_t erpi_gpio_irq_handler(unsigned int irq, 
                                           void *dev_id, struct pt_regs *regs) 
{   
    // ledOn = !ledOn;                          // toggle the LED state   
    // gpio_set_value(gpioLED, ledOn);          // set LED accordingly  
    numberPresses++;   
    printk(KERN_INFO "numberPresses is %d\n", 
           numberPresses);
                        //   global counter
    return (irq_handler_t) IRQ_HANDLED;      // announce IRQ handled 
}

module_init(erpi_gpio_init);
module_exit(erpi_gpio_exit);


