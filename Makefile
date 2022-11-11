CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = INC

all: *.c
	#$(CC) $(CFLAGS) -I $(INC)  delete.c -o ln_deleter
	#$(CC) $(CFLAGS) -I $(INC) join.c -o file_join
	$(CC) $(CFLAGS) -I $(INC)  file.c -o file

clean:
	rm -rf ln_deleter
	rm -rf file_join

re: clean all

.PHONY: re all clean fclean
