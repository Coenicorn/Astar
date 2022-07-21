EXEC := ./build/main.out

SRCDIR := ./src

CFLAGS := -Wall -g -I$(SRCDIR)/
LDLIBS := -ldl -lm -L$(SRCDIR)/

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:.c=.o)

RM := rm -rf

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

build: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $(EXEC) $(LDLIBS)
	# $(MAKE) clean

clean:
	sudo $(RM) $(SRCDIR)/*.o