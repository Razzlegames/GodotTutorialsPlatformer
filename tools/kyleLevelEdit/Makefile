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

# Take care of dependencies
CDEPS = $(CFILES:.c=.d)
CPPDEPS = $(CPPFILES:.cpp=.d)
DEPS = $(CDEPS) $(CPPDEPS)


all: $(BIN) tags

$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) $(LIBS) -o $(BIN) 

%.o: %.cpp 
	$(CC) -MMD -MP -MF $*.d $(CPPFLAGS) -c $*.cpp

%.o: %.c 
	$(CC) -MMD -MP -MF $*.d $(CPPFLAGS) -c $*.c

-include $(DEPS)

run: all
	./$(BIN)

#---------------------------------------------------------------------------------
#   Get rid of all the intermediary makefiles (.d files)
#---------------------------------------------------------------------------------
clean-deps:
	-rm $(DEPS)

clean: clean-deps
	rm -f *o $(BIN)

tags: $(SOURCES)
	-ctags -R --sort=yes --c++-kinds=+cdefgmnpstux \
	  --fields=+iaKS --extra=+q ./ ../ \
		/usr/include/gtk-2.0/ ./ /usr/include/FreeImage.h
