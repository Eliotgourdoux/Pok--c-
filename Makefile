##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Compileur
##

CC = g++
CFLAGS = -I include
CPPFLAGS = -Wall -Wextra

SRC = main.cpp \
	$(wildcard src/*.cpp)

OBJ = $(SRC:.cpp=.o)
NAME = pokemon_cpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS) $(CPFLAGS) -g3

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
