/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:55:24 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 22:10:11 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		set_name(char **file_path, char **tmp, char *dpath, char *entryname)
{
	if (!ft_strcmp(dpath, "/"))
	{
		if (!(*file_path = ft_strjoin(dpath, entryname)))
			return (0);
	}
	else
	{
		if (!(*tmp = ft_strjoin(dpath, "/")))
			return (0);
		if (!(*file_path = ft_strjoin(*tmp, entryname)))
		{
			free(*tmp);
			return (0);
		}
		free(*tmp);
	}
	return (1);
}

int		set_name2(char **file_path, char **name, char *entryname)
{
	if (!(*name = ft_strdup(entryname)))
	{
		free(*file_path);
		return (0);
	}
	return (1);
}

int		set_dlist(t_flist **flist, t_flist **tmp, char **file_path, char **name)
{
	if (!(*flist))
	{
		if (!(*flist = new_flist(*name, *file_path)))
		{
			free(*name);
			free(*file_path);
			return (0);
		}
	}
	else
	{
		if (!(*tmp = new_flist(*name, *file_path)))
		{
			free(*name);
			free(*file_path);
			return (0);
		}
		push_flist(flist, *tmp);
	}
	return (1);
}

int		open_dir(t_dlist *dlist, int options, t_flist *tmpflist)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*file_path;
	char			*tmp;
	char			*name;

	if ((dir = opendir(dlist->path)))
	{
		while ((entry = readdir(dir)))
		{
			if (entry->d_name[0] == '.' && !(options & OPTION_MIN_A)
				&& (!(options & OPTION_CAP_A
				&& ft_strcmp(entry->d_name, ".") != 0
				&& ft_strcmp(entry->d_name, "..") != 0)))
				continue;
			if (!set_name(&file_path, &tmp, dlist->path, entry->d_name)
				|| !set_name2(&file_path, &name, entry->d_name)
				|| !set_dlist(&dlist->flist, &tmpflist, &file_path, &name))
				return (0);
		}
		closedir(dir);
	}
	else
		dlist->errn = errno;
	return (1);
}
