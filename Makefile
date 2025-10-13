CC := gcc

SRCS := $(wildcard [0-9][0-9]*.c)
TARGETS := $(patsubst %.c,%,$(SRCS))
FILES_TO_CLEAN := $(TARGETS) tigr.o

CFLAGS :=

ifeq ($(OS),Windows_NT)
    LDFLAGS := -lopengl32 -lgdi32
	RM_CMD = del /q
else
    OS := $(shell uname -s)

    ifeq ($(OS),Darwin)
        LDFLAGS := -framework OpenGL -framework Cocoa
        RM_CMD = rm -f
    else ifeq ($(OS),Linux)
        LDFLAGS := -lGLU -lGL -lX11
        RM_CMD = rm -f
    else
        # unknown systems
        LDFLAGS :=
        RM_CMD = rm -f
        $(warning Unknown operating system ($(OS)). No link flags and using "rm -f" for cleanup.)
    endif
endif

.PHONY: all clean debug

all: $(TARGETS)

debug: CFLAGS += -g -O0
debug: $(TARGETS)

tigr.o: tigr.c
	$(CC) $(CFLAGS) -c $^

%: %.c tigr.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

99_meatballs: LDFLAGS += -lm

clean:
	$(RM_CMD) -f $(FILES_TO_CLEAN)