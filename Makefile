# Maxwell Kaye
# Comp15 HW4
# 3/8/18
# Makefile

CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11 -O2
DEPS = HashTable.h HashString.h LinkedList.h DirNode.h FSTree.h

%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

gerp: LinkedList.o HashTable.o HashString.o DirNode.o gerp.o FSTree.o
	$(CC) -o gerp LinkedList.o HashTable.o HashString.o DirNode.o gerp.o FSTree.o

clean:
	rm -f *.o core* *~ gerp
