CC = gcc
CFLAGS = -Wall -Wextra

TARGET = UTOPIA

$(TARGET): main.c logOrSignin.c management.c buying.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)