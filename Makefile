# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/08 20:51:06 by juhenriq          #+#    #+#              #
#    Updated: 2025/02/12 16:47:13 by juhenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX42_PATH = ./lib/MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_LIB_WITH_ITS_FLAGS = $(MLX42_LIB) -ldl -lglfw -pthread -lm






























###


NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

# MANDATORY_SRCS = 

# BONUS_SRCS = 

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	@$(MAKE) -C $(LIBFT_PATH)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(MANDATORY_OBJS)

bonus: clean_bonus $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_PATH)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(BONUS_OBJS)

clean_bonus:
	rm -f $(MANDATORY_OBJS)

mandatory/%.o: mandatory/%.c ft_printf.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c ft_printf_bonus.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all bonus clean fclean re
