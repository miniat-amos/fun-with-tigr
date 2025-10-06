CC := gcc

SRCS := $(wildcard [0-9][0-9]*.c)
TARGETS := $(patsubst %.c,%,$(SRCS))
FILES_TO_CLEAN := $(TARGETS) tigr.o

CFLAGS :=

# Get lowercase OS name (linux, darwin, windows)
OS := $(shell uname -s | tr '[:upper:]' '[:lower:]')

ifeq ($(OS),windows)
    LDFLAGS := -lopengl32 -lgdi32
	RM_CMD = del /q
else ifeq ($(OS),darwin)
    LDFLAGS := -framework OpenGL -framework Cocoa
	RM_CMD = rm -f
else ifeq ($(OS),linux)
    LDFLAGS := -lGLU -lGL -lX11
	RM_CMD = rm -f
else
    # unknown systems
    LDFLAGS :=
    RM_CMD = rm -f
    $(warning Unknown operating system ($(OS)). No link flags and using "rm -f" for cleanup.)
endif

.PHONY: all clean debug

all: $(TARGETS)

debug: CFLAGS += -g -O0
debug: $(TARGETS)

tigr.o: tigr.c
	$(CC) $(CFLAGS) -c $^

%: %.c tigr.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM_CMD) -f $(FILES_TO_CLEAN)