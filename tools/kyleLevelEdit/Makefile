CC=g++
CPPFLAGS= -Wall -g -export-dynamic `pkg-config --cflags --libs gtk+-2.0` 
LIBS= -lfreeimage
BIN=tutorial

OBJS= $(patsubst %.cpp,%.o,$(wildcard *.cpp)) \
      $(patsubst %.c,%.o,$(wildcard *.c)) \

#---------------------------------------------------------------------------------
#  Account for normal c/cpp files
#---------------------------------------------------------------------------------
CFILES := $(wildcard *.c)
CPPFILES := $(wildcard *.cpp)
SOURCES := $(CFILES) $(CPPFILES)


all: $(BIN) tags

$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) $(LIBS) -o $(BIN) 

%.o: %.cpp 
	$(CC) $(CPPFLAGS) -c $*.cpp

%.o: %.c 
	$(CC) $(CPPFLAGS) -c $*.c

run: all
	./$(BIN)

clean:
	rm -f *o $(BIN)

tags: $(SOURCES)
	-ctags -R --sort=yes --c++-kinds=+cdefgmnpstux \
	  --fields=+iaKS --extra=+q ./ ../ \
		/usr/include/gtk-2.0/ ./ /usr/include/FreeImage.h
