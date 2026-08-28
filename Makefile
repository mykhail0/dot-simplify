CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -fstack-protector-strong -g

.PHONY: all clean test

SRCDIR = src
BUILDDIR = build
TESTSDIR = tests
EXECUTABLE = $(BUILDDIR)/dot-simplify
AUXOBJS = $(BUILDDIR)/bst.o $(BUILDDIR)/darr.o $(BUILDDIR)/input.o

all: $(EXECUTABLE)

$(EXECUTABLE): $(BUILDDIR)/dot-simplify.o $(AUXOBJS)
	$(CC) -o $@ $^

$(BUILDDIR)/dot-simplify.o: $(SRCDIR)/dot-simplify.c $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	if [ -d "$(BUILDDIR)" ]; then rm -rf "$(BUILDDIR)"; fi
	find "$(TESTSDIR)" -name "*.t" -delete

test: $(EXECUTABLE) test.sh $(TESTSDIR)
	./test.sh
