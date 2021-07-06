# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/12 15:03:29 by pcharrie          #+#    #+#              #
#    Updated: 2020/03/10 11:50:02 by pcharrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I include

SRCS =	src/builtin.c		\
		src/builtin2.c		\
		src/cmd.c			\
		src/env.c			\
		src/env2.c			\
		src/error.c			\
		src/main.c			\
		src/ms.c			\
		src/ms2.c			\
		src/print.c			\
		src/signal.c		\
		src/split.c			\
		src/split2.c		\
		src/stdin.c			\
		src/stdin2.c		\
		src/utils.c			\
		src/utils2.c		\
		src/utils3.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) include/minishell.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	/bin/rm -rf $(OBJS)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
