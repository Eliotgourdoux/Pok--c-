##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Compileur
##

CC = g++
CPPFLAGS = -Wall -Wextra -I include
RAYLIBFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.cpp \
	$(wildcard src/*.cpp)

OBJ = $(SRC:.cpp=.o)
NAME = pokemon_cpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS) $(RAYLIBFLAGS) -g3

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
