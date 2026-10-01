SHELL :=/bin/bash

CC := clang -g
CFLAGS := -Wall -Wextra -Werror -Iincs/
LIBFT := libft/libft.a
LIBX = minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a
SRC_DIRS := src
NAME := cub3d

$(NAME):
	$(CC) $(CFLAGS) src/*.c $(LIBFT) $(LIBX) -lXext -lX11 -lm -o $(NAME)

all: $(NAME)
