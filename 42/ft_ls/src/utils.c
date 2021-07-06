/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:58:50 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 20:55:46 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_ls.h"

void	ft_put_whitespaces(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putstr(" ");
		i++;
	}
}

void	ft_putchar_fd(int fd, char c)
{
	char str[2];

	str[0] = c;
	str[1] = '\0';
	ft_putstr_fd(fd, str);
}

void	ft_putstr_fd(int fd, char *str)
{
	static int	i[3] = {0, 0, 0};
	static char	mstr[3][4096];

	if (fd >= 0 && fd <= 2)
	{
		while (*str != '\0')
		{
			mstr[fd][i[fd]] = *str;
			i[fd]++;
			if (*str == '\n' || i[fd] == 4096 - 1)
			{
				mstr[fd][i[fd]] = '\0';
				write(fd, mstr[fd], i[fd]);
				i[fd] = 0;
			}
			str++;
		}
	}
}

int		double_char_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (0);
}

int		flist_len(t_flist *flist)
{
	int i;

	i = 0;
	while (flist)
	{
		i++;
		flist = flist->next;
	}
	return (i);
}
