# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 16:21:33 by pcharrie          #+#    #+#              #
#    Updated: 2019/02/27 20:32:44 by pcharrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I include

SRCS =	src/cmp.c						\
		src/cmp2.c						\
		src/delete.c					\
		src/error.c						\
		src/main.c						\
		src/merge.c						\
		src/new.c						\
		src/new2.c						\
		src/options.c					\
		src/parse_argv.c				\
		src/print.c						\
		src/print2.c					\
		src/print_flist_cols.c			\
		src/print_flist_linebreak.c		\
		src/print_flist_long.c			\
		src/print_flist_long2.c			\
		src/print_flist_long3.c			\
		src/print_flist_long4.c			\
		src/print_flist_long5.c			\
		src/print_flist_long_date.c		\
		src/push.c						\
		src/recursive_flist.c			\
		src/sort.c						\
		src/sort_dlist.c				\
		src/utils.c						\
		src/utils2.c					\
		src/utils3.c					\
		src/utils4.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) include/ft_ls.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
