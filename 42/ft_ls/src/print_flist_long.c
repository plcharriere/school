/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:34:34 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/27 19:24:55 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_nlink_max(t_flist *flist)
{
	int max;

	max = 0;
	while (flist)
	{
		if (ft_nblen(flist->f->stat.st_nlink) > max)
			max = ft_nblen(flist->f->stat.st_nlink);
		flist = flist->next;
	}
	return (max);
}

int		get_username_max(t_flist *flist)
{
	int max;

	max = 0;
	while (flist)
	{
		if (!flist->f->passwd.pw_name)
		{
			if (ft_nblen(flist->f->stat.st_uid) > max)
				max = ft_nblen(flist->f->stat.st_uid);
		}
		else if (ft_strlen(flist->f->passwd.pw_name) > max)
			max = ft_strlen(flist->f->passwd.pw_name);
		flist = flist->next;
	}
	return (max);
}

int		get_groupname_max(t_flist *flist)
{
	int max;

	max = 0;
	while (flist)
	{
		if (!flist->f->passwd.pw_name)
		{
			if (ft_nblen(flist->f->stat.st_gid) > max)
				max = ft_nblen(flist->f->stat.st_gid);
		}
		else if (flist->f->group.gr_name
			&& ft_strlen(flist->f->group.gr_name) > max)
			max = ft_strlen(flist->f->group.gr_name);
		flist = flist->next;
	}
	return (max);
}
