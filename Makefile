# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/07 00:56:57 by aait-ihi          #+#    #+#              #
#    Updated: 2019/12/11 03:18:55 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = readline

CFLAGS = -Wall -Werror -Wextra -g

CC = gcc

SRCS = main.c helper.c  cursor_move.c signal.c

LIBFT = libft/libft.a

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) -g $(CFLAGS) $(OBJ) $(LIBFT) -ltermcap -o $(NAME)

$(LIBFT) : libf

libf :
	make -C libft
$(OBJ) : ft_readline.h

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
