/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_long5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:45:57 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/27 17:57:49 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_name2(t_f *f)
{
	int i;

	i = 0;
	while (f->name[i])
	{
		if (i == ft_strlen(f->name) - 1 && (f->name[i] == '/'
				|| f->name[i] == '|' || f->name[i] == '=' || f->name[i] == '@'
				|| f->name[i] == '*')
			&& f->name[i] != f->path[ft_strlen(f->path) - 1])
			ft_putstr("\x1B[0m");
		ft_putchar(f->name[i]);
		i++;
	}
	ft_putstr("\x1B[0m");
}

void	print_file_name(t_f *f, int options)
{
	struct termios	term;

	if (options & OPTION_CAP_G && tcgetattr(1, &term) == 0)
	{
		if (S_ISCHR(f->stat.st_mode))
			ft_putstr("\x1B[43;34m");
		else if (S_ISSOCK(f->stat.st_mode))
			ft_putstr("\x1B[32m");
		else if (S_ISBLK(f->stat.st_mode))
			ft_putstr("\x1B[46;34m");
		else if (f->stat.st_mode & S_ISVTX && f->stat.st_mode & S_IWOTH)
			ft_putstr("\x1B[42;30m");
		else if (f->stat.st_mode & S_ISUID)
			ft_putstr("\x1B[41;30m");
		else if (f->stat.st_mode & S_ISGID)
			ft_putstr("\x1B[46;30m");
		else if (S_ISLNK(f->stat.st_mode))
			ft_putstr("\x1B[35m");
		else if (S_ISDIR(f->stat.st_mode))
			ft_putstr("\x1B[34m");
		else if (f->stat.st_mode & S_IXUSR)
			ft_putstr("\x1B[31m");
		return (print_file_name2(f));
	}
	ft_putstr(f->name);
}

void	print_file_type_permissions(t_f *f)
{
	if (S_ISLNK(f->stat.st_mode))
		ft_putchar('l');
	else if (S_ISBLK(f->stat.st_mode))
		ft_putchar('b');
	else if (S_ISCHR(f->stat.st_mode))
		ft_putchar('c');
	else if (S_ISSOCK(f->stat.st_mode))
		ft_putchar('s');
	else if (S_ISFIFO(f->stat.st_mode))
		ft_putchar('p');
	else if (f->stat.st_mode & S_IFDIR)
		ft_putchar('d');
	else
		ft_putchar('-');
	print_file_permissions(f);
}
