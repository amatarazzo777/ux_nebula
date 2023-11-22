#CC=clang
CC=g++
CFLAGS=-std=c++17 -Os
INCLUDES=-Ivm -Ivm/base -Ivm/os/linux_xcb
LFLAGS=`pkg-config --libs xcb-image`

debug: CFLAGS += -g
debug: test0.out

release: LFLAGS += -s
release: test0.out

all: test0.out

test0.out: main.o view_manager.o vector_font.o os_interface.o
	$(CC) -o guidom.out main.o view_manager.o vector_font.o os_interface.o -lstdc++ -lm -lxcb -lxcb-keysyms $(LFLAGS) 

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

view_manager.o: vm/base/view_manager.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c vm/base/view_manager.cpp -o view_manager.o

vector_font.o: vm/base/vector_font.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c vm/base/vector_font.cpp -o vector_font.o

os_interface.o: vm/base/os_interface.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c vm/base/os_interface.cpp -o os_interface.o

clean:
	rm *.o *.out
