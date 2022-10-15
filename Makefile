# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 13:53:10 by ymohamed          #+#    #+#              #
#    Updated: 2022/10/14 16:08:24 by ymohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SOURCES = \
		so_long.c so_ginitiate.c so_map_validation.c so_gactions.c so_gmoves.c \
		resources/get_next_line/get_next_line.c resources/get_next_line/get_next_line_utils.c \
		
OBJECTS = $(SOURCES:%.c=%.o)

LIBX = ./resources/mlx/libmlx.a
LIBFTBF = ./resources/ft_libft_printf/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(OBJECTS)
	$(MAKE) -C ./resources/mlx
	$(MAKE)	-C ./resources/ft_libft_printf
	$(CC) -o $(NAME) $(SOURCES) $(LIBX) $(LIBFTBF)  -framework OpenGL -framework AppKit

clean:
	$(MAKE) clean -C ./resources/mlx
	$(MAKE) clean -C ./resources/ft_libft_printf
	/bin/rm -f $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C ./resources/ft_libft_printf
	/bin/rm -f $(NAME)

re: fclean all
