OBJS = modbus_client.o test.o

# This is the default target, which will be built when you invoke make
all: modbus install clean

# This rule tells make how to build the files
modbus: $(OBJS)
	g++ -o modbus $(OBJS) -I include

%.o : src/%.cpp
	g++ -o $@ -c $< -I include

# This rule tells make to copy hello to the binaries subdirectory, creating it if necessary
install:
	mkdir -p bin
	cp -p modbus bin

# This rule tells make to delete hello
clean:
	rm -f modbus $(OBJS)
