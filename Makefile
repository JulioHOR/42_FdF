# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/08 20:51:06 by juhenriq          #+#    #+#              #
#    Updated: 2025/03/10 23:17:32 by juhenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g -O0
else
    CFLAGS += -Ofast
endif

MLX42_PATH = ./MLX42
MLX42_BUILD = $(MLX42_PATH)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_DEPENDENCIES = -ldl -lglfw -pthread -lm

LIBFT_PATH = ./libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

INCLUDES = -I . -I $(MLX42_PATH)/include -I $(LIBFT_PATH)

SRCS = keyboard_control.c line_rendering_horizontal.c line_rendering_utils.c \
		line_rendering_vertical.c  map_get_functions.c line_rendering.c \
		map_loader.c  map_utils.c utils.c   map_rendering_functions.c main.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

debug: fclean
	@$(MAKE) DEBUG=1

$(NAME): libmlx $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX42_LIB) $(MLX42_DEPENDENCIES) -o $(NAME)

libmlx:
	@cmake -DDEBUG=$(DEBUG) $(MLX42_PATH) -B $(MLX42_BUILD)
	@make -C $(MLX42_BUILD) -j4

$(LIBFT_LIB):
ifeq ($(DEBUG), 0)
	@make -C $(LIBFT_PATH) all
else
	@make -C $(LIBFT_PATH) debug
endif

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(MLX42_BUILD)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re libmlx debug