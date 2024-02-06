CC := gcc

EXEC := ./build/main.out

SRCDIR := ./src
LIBDIR := ./lib
INCLUDEDIR := ./include
OBJDIR := ./obj

CFLAGS := -Wall -Wextra -g -I$(SRCDIR)/ -I$(INCLUDEDIR)/
LFLAGS := -L$(SRCDIR)/ -L$(LIBDIR)/
LDFLAGS := -lastar

OBJS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(OBJS:.c=.o)
OBJS := $(subst $(SRCDIR)/,$(OBJDIR)/,$(OBJS))

MKDIR := mkdir -p

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

all: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf EXEC