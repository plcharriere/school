/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_long3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:15:11 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/18 12:20:44 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_permissions(t_f *f)
{
	ft_putchar(f->stat.st_mode & S_IRUSR ? 'r' : '-');
	ft_putchar(f->stat.st_mode & S_IWUSR ? 'w' : '-');
	if (f->stat.st_mode & S_ISUID)
		ft_putchar(f->stat.st_mode & S_IXUSR ? 's' : 'S');
	else
		ft_putchar(f->stat.st_mode & S_IXUSR ? 'x' : '-');
	ft_putchar(f->stat.st_mode & S_IRGRP ? 'r' : '-');
	ft_putchar(f->stat.st_mode & S_IWGRP ? 'w' : '-');
	if (f->stat.st_mode & S_ISGID)
		ft_putchar(f->stat.st_mode & S_IXGRP ? 's' : 'S');
	else
		ft_putchar((f->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar(f->stat.st_mode & S_IROTH ? 'r' : '-');
	ft_putchar(f->stat.st_mode & S_IWOTH ? 'w' : '-');
	if (f->stat.st_mode & S_ISVTX)
		ft_putchar(f->stat.st_mode & S_IXOTH ? 't' : 'T');
	else
		ft_putchar(f->stat.st_mode & S_IXOTH ? 'x' : '-');
}

void	print_file_xattr(t_f *f)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;

	acl = acl_get_link_np(f->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(f->path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		ft_putchar('@');
	else if (acl != NULL)
		ft_putchar('+');
	else
		ft_putchar(' ');
	acl_free(acl);
	acl = NULL;
}

void	print_file_nlink(t_f *f, int max)
{
	int nb_space;
	int i;

	nb_space = max - ft_nblen(f->stat.st_nlink);
	i = 0;
	while (i < nb_space)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(f->stat.st_nlink);
}

void	print_file_username(t_f *f, int max)
{
	int nb_space;
	int i;

	if (!f->passwd.pw_name)
	{
		nb_space = max - ft_nblen(f->stat.st_uid);
		ft_putnbr(f->stat.st_uid);
	}
	else
	{
		nb_space = max - ft_strlen(f->passwd.pw_name);
		ft_putstr(f->passwd.pw_name);
	}
	i = 0;
	while (i < nb_space)
	{
		ft_putchar(' ');
		i++;
	}
}

void	print_file_groupname(t_f *f, int max)
{
	int nb_space;
	int i;

	if (!f->group.gr_name)
	{
		nb_space = max - ft_nblen(f->stat.st_gid);
		ft_putnbr(f->stat.st_gid);
	}
	else
	{
		nb_space = max - ft_strlen(f->group.gr_name);
		ft_putstr(f->group.gr_name);
	}
	i = 0;
	while (i < nb_space)
	{
		ft_putchar(' ');
		i++;
	}
}
