#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

MODULE_LICENSE("-");
MODULE_AUTHOR("Team 1");
MODULE_DESCRIPTION("Project 4, Part 1");
MODULE_VERSION("0.1");

static unsigned int gpioOut = 22; 
static unsigned int gpioIn = 17;  

static irqreturn_t gpio_link_irq_handler(int irq, void *dev_id)
{
    int inputValue = gpio_get_value(gpioIn);

    gpio_set_value(gpioOut, inputValue);

    printk(KERN_INFO "GPIO_LINK: Output: %d, Input: %d\n",
           gpio_get_value(gpioOut), gpio_get_value(gpioIn));

    return IRQ_HANDLED;
}

static int __init gpio_link_init(void)
{
    int result = 0;
    printk(KERN_INFO "GPIO_LINK: Init");

    gpio_request(gpioOut, "sysfs");
    gpio_request(gpioIn, "sysfs");

    gpio_direction_output(gpioOut, 0);
    gpio_direction_input(gpioIn);

    printk(KERN_INFO "GPIO_LINK: GPIO-Status - Ausgang: %d, Eingang: %d\n",
           gpio_get_value(gpioOut), gpio_get_value(gpioIn));

    result = request_irq(gpio_to_irq(gpioIn), gpio_link_irq_handler, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "gpio_link_irq_handler", NULL);

    return result;
}

static void __exit gpio_link_exit(void)
{
    free_irq(gpio_to_irq(gpioIn), NULL); 
    gpio_set_value(gpioOut, 0); 
    gpio_free(gpioOut);
    gpio_free(gpioIn);

    printk(KERN_INFO "GPIO_LINK closed");
}

module_init(gpio_link_init);
module_exit(gpio_link_exit);
