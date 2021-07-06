/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:26:12 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/27 18:12:02 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flist	*get_flist_index(t_flist *flist, int index, int reset)
{
	int				i;
	static t_flist	**cache = NULL;
	static int		size = 0;

	if (reset)
	{
		free(cache);
		cache = NULL;
		return (NULL);
	}
	if (!cache)
	{
		size = flist_len(flist);
		if (!(cache = (t_flist **)malloc(sizeof(t_flist *) * size)))
			return (NULL);
		i = 0;
		while (flist)
		{
			cache[i++] = flist;
			flist = flist->next;
		}
	}
	if (index >= size)
		return (NULL);
	return (cache[index]);
}

void	set_name_type(t_flist *flist)
{
	char	*tmp;
	t_f		*f;

	while (flist)
	{
		f = flist->f;
		tmp = NULL;
		if (S_ISLNK(f->stat.st_mode))
			tmp = ft_strjoin(f->name, "@");
		else if (S_ISFIFO(f->stat.st_mode))
			tmp = ft_strjoin(f->name, "|");
		else if (S_ISSOCK(f->stat.st_mode))
			tmp = ft_strjoin(f->name, "=");
		else if (S_ISDIR(f->stat.st_mode))
			tmp = ft_strjoin(f->name, "/");
		else if (f->stat.st_mode & S_IXUSR || f->stat.st_mode & S_IXGRP
		|| f->stat.st_mode & S_IXOTH)
			tmp = ft_strjoin(f->name, "*");
		if (tmp)
		{
			free(f->name);
			f->name = tmp;
		}
		flist = flist->next;
	}
}

void	set_dir_slash(t_flist *flist)
{
	char	*tmp;
	t_f		*f;

	while (flist)
	{
		f = flist->f;
		tmp = NULL;
		if (S_ISDIR(f->stat.st_mode))
			tmp = ft_strjoin(f->name, "/");
		if (tmp)
		{
			free(f->name);
			f->name = tmp;
		}
		flist = flist->next;
	}
}
