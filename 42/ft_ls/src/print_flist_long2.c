/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_long2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:14:45 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 18:28:05 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_size(t_f *f, int max)
{
	int nb_space;
	int i;

	nb_space = max - ft_nblen(f->stat.st_size);
	i = 0;
	while (i < nb_space)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(f->stat.st_size);
}

void	print_file_size_special(t_f *f, int max)
{
	int nb_space;
	int i;

	ft_putchar(' ');
	nb_space = max - ft_nblen(major(f->stat.st_rdev));
	i = 0;
	while (i < nb_space)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(major(f->stat.st_rdev));
	ft_putstr(", ");
	nb_space = 3 - ft_nblen(minor(f->stat.st_rdev));
	i = 0;
	while (i < nb_space)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(minor(f->stat.st_rdev));
}

void	print_file_name_long(t_f *f, int options)
{
	char	buf[256];
	ssize_t	count;

	print_file_name(f, options);
	if (S_ISLNK(f->stat.st_mode))
	{
		if ((count = readlink(f->path, buf, 256)) != -1)
		{
			buf[count] = '\0';
			ft_putstr(" -> ");
			ft_putstr(buf);
		}
	}
}
