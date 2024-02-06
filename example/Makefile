EXEC := ./build/main.out

SRCDIR := ./src

LIBDIR := ./lib
INCLUDEDIR := ./include

CFLAGS := -Wall -g -I$(SRCDIR)/ -I$(INCLUDEDIR)/
LFLAGS := -L$(SRCDIR)/ -L$(LIBDIR)/
LDFLAGS := -lastar -lraylib -lpthread -lGL -ldl -lm

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

all: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -rf $(SRCDIR)/*.o
	rm -rf $EXEC