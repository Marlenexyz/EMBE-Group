OBJS = modbus_server.o main.o

# This is the default target, which will be built when you invoke make
all: main install clean

# This rule tells make how to build the files
main: $(OBJS)
	g++ -o main $(OBJS) -I include -l pthread

%.o : src/%.cpp
	g++ -o $@ -c $< -I include -l pthread

# This rule tells make to copy hello to the binaries subdirectory, creating it if necessary
install:
	mkdir -p bin
	cp -p main bin

# This rule tells make to delete hello
clean:
	rm -f main $(OBJS)
