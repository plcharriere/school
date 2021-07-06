/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:59:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/27 16:54:41 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>

# define BUFF_SIZE	10000

int				get_next_line(const int fd, char **line);

typedef struct	s_gnl
{
	char	b[OPEN_MAX][BUFF_SIZE];
	int		i[OPEN_MAX];
	int		c[OPEN_MAX];
	int		j;
}				t_gnl;

#endif
