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


run: all
	./$(BIN)

