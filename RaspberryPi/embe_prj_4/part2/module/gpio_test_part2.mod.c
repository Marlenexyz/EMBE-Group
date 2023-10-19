#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x4e3699d0, "gpio_to_desc" },
	{ 0x15fa3b39, "gpiod_get_raw_value" },
	{ 0x92997ed8, "_printk" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xaa2fdd5a, "gpiod_unexport" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xb6dab8e2, "gpiod_direction_input" },
	{ 0x93cc37df, "gpiod_export" },
	{ 0x4181de0, "gpiod_to_irq" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x89588b47, "kernel_kobj" },
	{ 0x2f4b5a10, "kobject_create_and_add" },
	{ 0x8baff743, "sysfs_create_file_ns" },
	{ 0x1d9b1bb4, "kobject_put" },
	{ 0xe3035aa9, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C1D8F15F11A8875810871EF");
