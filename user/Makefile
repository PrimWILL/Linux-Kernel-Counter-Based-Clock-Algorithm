CC = gcc
OBJS = test.o
OBJS2 = test2.o
TARGET = test
TARGET2 = test2

all:
	make test
	make test2

test: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	@rm -f $(OBJS)

test2: $(OBJS2)
	$(CC) $(OBJS2) -o $(TARGET2)
	@rm -f $(OBJS2)

test.o: test.c
	$(CC) -c test.c

test2.o: test2.c
	$(CC) -c test2.c

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f $(TARGET2)
