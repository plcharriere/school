# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 08:35:16 by marvin            #+#    #+#              #
#    Updated: 2019/08/26 22:15:10 by pcharrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I include

LIBS = -ltermcap

SRCS =	src/args.c		\
		src/args2.c		\
		src/args3.c		\
		src/error.c		\
		src/keys.c		\
		src/keys2.c		\
		src/main.c		\
		src/print.c		\
		src/print2.c	\
		src/signals.c	\
		src/signals2.c	\
		src/term.c		\
		src/term2.c		\
		src/utils.c		\
		src/utils2.c	\
		src/utils3.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o			:			%.c include/ft_select.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) include/ft_select.h
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	/bin/rm -rf $(OBJS)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
