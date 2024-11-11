CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
NAME=s21_grep

all:$(NAME)

s21_grep: $(NAME).c
	$(CC) $^ $(CFLAGS) -o $(NAME)

test: rebuild 
	bash Greptest.sh

clang:
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h

rebuild: clean all

clean:
	rm -rf $(NAME)
	rm -rf *.log