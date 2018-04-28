CC=g++
CPPFLAGS=-I. -std=c++11
DEPS=util.h
PROGRAMS=00-empty 01-plain 02-multi-instance 03-static 04-permutate-layout 05-inheritance-instance-order 06-inheritance-instance-order2 07-inheritance-layout 08-inheritance-layout2 09-inheritance-cast 10-vtable-layout 11-vtable-inheritance 13-vtable-multi-base

all: $(PROGRAMS) $(DEPS)
clean:
	rm -rf $(PROGRAMS)