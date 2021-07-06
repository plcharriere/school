/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:14:47 by pcharrie          #+#    #+#             */
/*   Updated: 2019/04/25 22:38:58 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putchar(char c)
{
	ft_putchar_fd(1, c);
}

void	ft_putstr_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putstr(char *s)
{
	ft_putstr_fd(1, s);
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
