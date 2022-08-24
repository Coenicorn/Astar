EXEC := ./build/main.out

SRCDIR := ./src
BINDIR := ./bin
LIBDIR := ./lib
OBJDIR := ./obj

CFLAGS := -Wall -Wextra -g -I$(SRCDIR)/ -I$(LIBDIR)/
LFLAGS := -L$(SRCDIR)/ -L$(BINDIR)/
LDFLAGS := 

OBJS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(OBJS:.c=.o)
OBJS := $(subst $(SRCDIR)/,$(OBJDIR)/,$(OBJS))

MKDIR := mkdir -p

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

$(EXEC): $(OBJS)
	$(MKDIR) $(@D)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $(EXEC) $(LDFLAGS)
