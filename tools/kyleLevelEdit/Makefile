CC=g++
CPPFLAGS= -Wall -g -export-dynamic `pkg-config --cflags --libs gtk+-2.0` 
LIBS= -lfreeimage
BIN=tutorial

OBJS= $(patsubst %.cpp,%.o,$(wildcard *.cpp)) \
      $(patsubst %.c,%.o,$(wildcard *.c)) \


all: $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) $(LIBS) -o $(BIN) 


%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $*.cpp

%.o: %.c
	$(CC) $(CPPFLAGS) -c $*.c


run: all
	./$(BIN)

clean:
	rm -f *o $(BIN)

ctags:
	ctags -R /usr/include/gtk-2.0/ ./ /usr/include/FreeImage.h
