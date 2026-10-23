# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/08 19:30:00 by mafarsha          #+#    #+#              #
#    Updated: 2026/10/08 20:20:38 by mafarsha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := cub3d
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iincs -Ilibft/incs -Iminilibx-linux

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

MLX_DIR     := minilibx-linux
MLX         := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS_DIR    := src
OBJS_DIR    := objs

SRCS        := $(SRCS_DIR)/init_window.c \
               $(SRCS_DIR)/parsing/parse_file.c \
               $(SRCS_DIR)/parsing/parse_utils.c \
               $(SRCS_DIR)/parsing/parse_textures.c \
               $(SRCS_DIR)/parsing/parse_colors.c \
               $(SRCS_DIR)/parsing/parse_map.c \
               $(SRCS_DIR)/parsing/parse_walls.c \
               $(SRCS_DIR)/parsing/parse_main.c

OBJS        := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c incs/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re 
