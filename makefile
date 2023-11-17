#CC=clang
CC=g++
CFLAGS=-std=c++17 -Os
INCLUDES=-Ivm -Ivm/base
LFLAGS=`pkg-config --libs xcb-image`

debug: CFLAGS += -g
debug: test0.out

release: LFLAGS += -s
release: test0.out


test0.out: main.o view_manager.o vector_font.o display_node.o raster.o os_interface.o
	$(CC) -o guidom.out main.o view_manager.o vector_font.o display_node.o raster.o os_interface.o -lstdc++ -lm -lxcb -lxcb-keysyms $(LFLAGS) 

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

view_manager.o: view_manager.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c view_manager.cpp -o view_manager.o

display_node.o: display_node.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c display_node.cpp -o display_node.o

raster.o: raster.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c raster.cpp -o raster.o

vector_font.o: vector_font.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c vector_font.cpp -o vector_font.o

os_interface.o: os_interface.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c os_interface.cpp -o os_interface.o

clean:
	rm *.o *.out

