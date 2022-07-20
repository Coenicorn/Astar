EXEC := ../build/main

CFLAGS := -Wall -g -I.
LDFLAGS := -L.
LDLIBS := -ldl -lm

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

RM := rm -rf

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXEC) $(LDLIBS)
	$(MAKE) clean_obj

.PHONY: clean_obj

clean_obj:
	sudo $(RM) *.o
                    
