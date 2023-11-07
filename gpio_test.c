#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EMBE Team the Best");
MODULE_DESCRIPTION("Project 4 Part 1; 4th Implementation");
MODULE_VERSION("0.1");

static unsigned int gpioLED = 17; // pin 11 (GPIO17)
static unsigned int gpioOut = 22; // pin 15 (GPIO22)
static unsigned int irqNumberRising; // IRQ num for rising edge
static unsigned int irqNumberFalling; // IRQ num for falling edge
static bool ledOn = 0; // used to invert state of LED
static bool outOn = 0; // used to set state of GPIO Pin 22

static irq_handler_t erpi_gpio_irq_rising_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t erpi_gpio_irq_falling_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

static int __init erpi_gpio_init(void)
{
    int result = 0;
    printk(KERN_INFO "GPIO_TEST: Initializing the GPIO_TEST LKM\n");

    if (!gpio_is_valid(gpioLED) || !gpio_is_valid(gpioOut))
    {
        printk(KERN_INFO "GPIO_TEST: invalid LED or Output GPIO\n");
        return -ENODEV;
    }

    ledOn = true;
    outOn = false; // Set the initial state of GPIO Pin 22 to LOW (0)

    gpio_request(gpioLED, "sysfs"); // request LED GPIO
    gpio_request(gpioOut, "sysfs"); // request Output GPIO

    gpio_direction_output(gpioLED, ledOn); // set LED in output mode and on
    gpio_export(gpioLED, false); // appears in /sys/class/gpio
    gpio_direction_output(gpioOut, outOn); // set Output in output mode and LOW
    gpio_export(gpioOut, false); // appears in /sys/class/gpio

    printk(KERN_INFO "GPIO_TEST: LED is ON, Output is LOW\n");

    // Request IRQ for rising edge
    irqNumberRising = gpio_to_irq(gpioLED); // map GPIO LED to IRQ number
    printk(KERN_INFO "GPIO_TEST: LED mapped to IRQ (Rising): %d\n", irqNumberRising);
    result = request_irq(irqNumberRising, (irq_handler_t)erpi_gpio_irq_rising_handler, IRQF_TRIGGER_RISING, "erpi_gpio_rising_handler", NULL);
    printk(KERN_INFO "GPIO_TEST: IRQ (Rising) request result is: %d\n", result);

    // Request IRQ for falling edge
    irqNumberFalling = gpio_to_irq(gpioLED); // map GPIO LED to IRQ number
    printk(KERN_INFO "GPIO_TEST: LED mapped to IRQ (Falling): %d\n", irqNumberFalling);
    result = request_irq(irqNumberFalling, (irq_handler_t)erpi_gpio_irq_falling_handler, IRQF_TRIGGER_FALLING, "erpi_gpio_falling_handler", NULL);
    printk(KERN_INFO "GPIO_TEST: IRQ (Falling) request result is: %d\n", result);

    return result;
}

static void __exit erpi_gpio_exit(void)
{
    gpio_set_value(gpioLED, 0); // turn the LED off
    gpio_set_value(gpioOut, 0); // set GPIO Pin 22 to LOW
    gpio_unexport(gpioLED); // unexport the LED GPIO
    gpio_unexport(gpioOut); // unexport the Output GPIO
    free_irq(irqNumberRising, NULL); // free the IRQ number for rising edge
    free_irq(irqNumberFalling, NULL); // free the IRQ number for falling edge
    gpio_free(gpioLED); // free the LED GPIO
    gpio_free(gpioOut); // free the Output GPIO
    printk(KERN_INFO "GPIO_TEST: Goodbye from the LKM!\n");
}

static irq_handler_t erpi_gpio_irq_rising_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    ledOn = true; // Set LED state to ON (1)
    outOn = true; // Set GPIO Pin 22 state to HIGH (1)
    gpio_set_value(gpioLED, ledOn); // set LED accordingly
    gpio_set_value(gpioOut, outOn); // set GPIO Pin 22 accordingly
    printk(KERN_INFO "GPIO_TEST: Interrupt (Rising)! (LED is %d)\n", ledOn);
    return (irq_handler_t)IRQ_HANDLED; // announce IRQ handled
}

static irq_handler_t erpi_gpio_irq_falling_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    ledOn = false; // Set LED state to OFF (0)
    outOn = false; // Set GPIO Pin 22 state to LOW (0)
    gpio_set_value(gpioLED, ledOn); // set LED accordingly
    gpio_set_value(gpioOut, outOn); // set GPIO Pin 22 accordingly
    printk(KERN_INFO "GPIO_TEST: Interrupt (Falling)! (LED is %d)\n", ledOn);
    return (irq_handler_t)IRQ_HANDLED; // announce IRQ handled
}

module_init(erpi_gpio_init);
module_exit(erpi_gpio_exit);
