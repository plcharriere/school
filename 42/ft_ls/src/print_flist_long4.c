/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_long4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:15:42 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/18 13:03:51 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_file_size_max(t_flist *flist)
{
	int max;

	max = 0;
	while (flist)
	{
		if (ft_nblen(flist->f->stat.st_size) > max)
			max = ft_nblen(flist->f->stat.st_size);
		flist = flist->next;
	}
	return (max);
}

int		get_file_specialsize_max(t_flist *flist)
{
	int max;

	max = 0;
	while (flist)
	{
		if (S_ISBLK(flist->f->stat.st_mode) || S_ISCHR(flist->f->stat.st_mode))
		{
			if (ft_nblen(major(flist->f->stat.st_rdev)) > max)
				max = ft_nblen(major(flist->f->stat.st_rdev));
		}
		flist = flist->next;
	}
	if (max != 0)
		max += 5;
	return (max);
}

void	print_flist_long2(t_flist *list, int options, t_longmaxs *maxs)
{
	if (!(options & OPTION_MIN_G))
	{
		print_file_username(list->f, maxs->username_max);
		ft_putstr("  ");
	}
	if (!(options & OPTION_MIN_O))
	{
		print_file_groupname(list->f, maxs->groupname_max);
		ft_putstr("  ");
	}
	if (options & OPTION_MIN_O && options & OPTION_MIN_G)
		ft_putstr("  ");
	if (S_ISBLK(list->f->stat.st_mode) || S_ISCHR(list->f->stat.st_mode))
		print_file_size_special(list->f, (maxs->size_max > maxs->sizespecial_max
		? maxs->size_max : maxs->sizespecial_max));
	else
		print_file_size(list->f, (maxs->size_max > maxs->sizespecial_max
		? maxs->size_max : maxs->sizespecial_max));
	ft_putchar(' ');
	print_file_date(list->f, options);
	ft_putchar(' ');
	print_file_name_long(list->f, options);
	ft_putchar('\n');
}

void	print_flist_long(t_flist *flist, int options, int total)
{
	t_flist		*list;
	t_longmaxs	maxs;

	maxs.nlink_max = get_nlink_max(flist);
	maxs.username_max = get_username_max(flist);
	maxs.groupname_max = get_groupname_max(flist);
	maxs.size_max = get_file_size_max(flist);
	maxs.sizespecial_max = get_file_specialsize_max(flist);
	if (flist && total)
		print_flist_total(flist);
	list = flist;
	while (list)
	{
		print_file_type_permissions(list->f);
		print_file_xattr(list->f);
		ft_putchar(' ');
		print_file_nlink(list->f, maxs.nlink_max);
		ft_putchar(' ');
		print_flist_long2(list, options, &maxs);
		list = list->next;
	}
}

void	print_flist_total(t_flist *flist)
{
	int total;

	total = 0;
	while (flist)
	{
		if (flist->f->errn != 0)
			continue;
		total += flist->f->stat.st_blocks;
		flist = flist->next;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}
