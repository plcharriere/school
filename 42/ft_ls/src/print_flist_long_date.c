/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_long_date.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:55:21 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/18 12:55:53 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_date1(char *str)
{
	int i;

	i = 4;
	while (str[i] && str[i] != '\n')
	{
		if (i > 19)
			while (str[i] == ' ')
				i++;
		ft_putchar(str[i]);
		i++;
	}
}

void	print_file_date2(char *str)
{
	int i;

	i = 4;
	while (i < 10)
		ft_putchar(str[i++]);
	ft_putchar(' ');
	i = 19;
	while (str[i] && str[i] == ' ')
		i++;
	i--;
	while (str[i] && str[i] != '\n')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	print_file_date3(char *str)
{
	int i;

	i = 4;
	while (i < 16)
		ft_putchar(str[i++]);
}

void	print_file_date(t_f *f, int options)
{
	char	*str;
	time_t	now;
	time_t	file_time;
	time_t	diff;

	if (options & OPTION_MIN_U)
		file_time = f->stat.st_atime;
	else if (options & OPTION_CAP_U)
		file_time = f->stat.st_birthtime;
	else if (options & OPTION_MIN_C)
		file_time = f->stat.st_ctime;
	else
		file_time = f->stat.st_mtime;
	now = time(0);
	diff = now - file_time;
	str = ctime(&file_time);
	if (options & OPTION_CAP_T)
		print_file_date1(str);
	else if (diff >= 15778800 || file_time > now)
		print_file_date2(str);
	else
		print_file_date3(str);
}
