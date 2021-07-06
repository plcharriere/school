/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:49:08 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 19:33:31 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_name(t_flist *flist1, t_flist *flist2)
{
	return (ft_strcmp(flist1->f->name, flist2->f->name) < 0);
}

int		cmp_size(t_flist *flist1, t_flist *flist2)
{
	if (flist1->f->stat.st_size == flist2->f->stat.st_size)
	{
		return (ft_strcmp(flist1->f->name, flist2->f->name) < 0);
	}
	else
		return (flist1->f->stat.st_size > flist2->f->stat.st_size);
}

int		cmp_mtime(t_flist *flist1, t_flist *flist2)
{
	if (flist1->f->stat.st_mtime == flist2->f->stat.st_mtime)
	{
		return (ft_strcmp(flist1->f->name, flist2->f->name) < 0);
	}
	else
		return (flist1->f->stat.st_mtime > flist2->f->stat.st_mtime);
}

int		cmp_atime(t_flist *flist1, t_flist *flist2)
{
	if (flist1->f->stat.st_atime == flist2->f->stat.st_atime)
	{
		return (ft_strcmp(flist1->f->name, flist2->f->name) < 0);
	}
	else
		return (flist1->f->stat.st_atime > flist2->f->stat.st_atime);
}

int		cmp_ctime(t_flist *flist1, t_flist *flist2)
{
	if (flist1->f->stat.st_ctime == flist2->f->stat.st_ctime)
	{
		return (ft_strcmp(flist1->f->name, flist2->f->name) < 0);
	}
	else
		return (flist1->f->stat.st_ctime > flist2->f->stat.st_ctime);
}
