CC = gcc
TARGET = example
SRCS = $(shell find ./ -name "*.c")
INCS = $(shell find ./ -name "*.h")
OBJS = $(SRCS: %.c = %.o)

TARGET: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.c $(INCS)
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
