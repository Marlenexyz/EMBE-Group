obj-m+=gpio_test_part2.o
MODULE_NAME = gpio_test_part2

all: build #clean

build:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	# @mkdir -p output												#erstellt Unterordner if not vorhanden
	# @mv $(MODULE_NAME).ko output/$(MODULE_NAME).ko					#move
	# @mv $(MODULE_NAME).o output/$(MODULE_NAME).o
	# @mv $(MODULE_NAME).mod.c output/$(MODULE_NAME).mod.c
	# @mv $(MODULE_NAME).cmd output/$(MODULE_NAME).cmd
	# @mv $(MODULE_NAME).mod.o.d output/$(MODULE_NAME).mod.o.d
	# @mv $(MODULE_NAME).mod.o.cmd output/$(MODULE_NAME).mod.o.cmd
	# @mv Modules.symvers output/Modules.symvers
	# @mv modules.order output/modules.order

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	# @rm -rf output