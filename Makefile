CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = INC

all: *.c
	$(CC) $(CFLAGS) -I $(INC)  file.c -o file

clean:
	rm -rf file

re: clean all

.PHONY: re all clean fclean
