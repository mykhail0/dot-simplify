CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -fstack-protector-strong -g

.PHONY: all clean test

SRCDIR = src
BUILDDIR = build
TESTSDIR = tests
EXECUTABLE = $(BUILDDIR)/dot-simplify

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRCDIR)/dot-simplify.c $(BUILDDIR)/bst.o
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/dot-simplify.o
	$(CC) -o $@ $(BUILDDIR)/dot-simplify.o $(BUILDDIR)/bst.o

$(BUILDDIR)/bst.o: $(SRCDIR)/bst.c $(SRCDIR)/bst.h
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if [ -d "$(BUILDDIR)" ]; then rm -rf "$(BUILDDIR)"; fi
	find "$(TESTSDIR)" -name "*.myout" -delete

test: $(EXECUTABLE) test.sh $(TESTSDIR)
	./test.sh
