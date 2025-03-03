# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 19:42:29 by juhenriq          #+#    #+#              #
#    Updated: 2025/03/03 02:18:10 by juhenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g -O0
    NAME := $(NAME)
endif

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_strcmp_homemade.c is_hex.c
	
BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

FT_PRINTF_SRCS = ft_printf/ft_printf.c ft_printf/prepare_string.c \
	ft_printf/prepare_string_utils.c ft_printf/printf_logic_utils.c \
	ft_printf/to_string_char.c ft_printf/to_string_hex.c \
	ft_printf/to_string_int.c ft_printf/to_string_percent.c \
	ft_printf/to_string_pointer.c ft_printf/to_string_string.c \
	ft_printf/to_string_unsigned_int.c ft_printf/to_string_unsigned_int_to_hex.c \
	ft_printf/utils.c ft_printf/flag_alignment.c \
	ft_printf/format_especifier_content.c ft_printf/flag_width.c \
	ft_printf/flag_fill_zero.c ft_printf/flag_precision.c \
	ft_printf/flag_prefixe.c ft_printf/flag_force_plus_sign.c \
	ft_printf/flag_insert_spaces.c ft_printf/flag_fill_zero_utils.c \
	ft_printf/flag_precision_utils.c ft_printf/flag_utils.c

GET_NEXT_LINE_SRCS = get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:ft_printf/%.c=ft_printf/%.o)

GET_NEXT_LINE_OBJS = $(GET_NEXT_LINE_SRCS:get_next_line/%.c=get_next_line/%.o)

$(NAME): $(OBJS) $(BONUS_OBJS) $(FT_PRINTF_OBJS) $(GET_NEXT_LINE_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS) $(FT_PRINTF_OBJS) $(GET_NEXT_LINE_OBJS)

all: $(NAME)

debug: fclean
	@$(MAKE) DEBUG=1 all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ft_printf/%.o: ft_printf/%.c
	$(CC) $(CFLAGS) -c $< -o $@

get_next_line/%.o: get_next_line/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	- rm -f $(OBJS) $(BONUS_OBJS) $(FT_PRINTF_OBJS) $(GET_NEXT_LINE_OBJS)

fclean: clean
	- rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
