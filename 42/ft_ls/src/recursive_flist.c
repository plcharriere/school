/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_flist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:26:02 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/25 21:20:21 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursive_flist(t_flist *flist, int options)
{
	while (flist)
	{
		if (ft_strcmp(flist->f->name, ".") != 0
			&& ft_strcmp(flist->f->name, "..") != 0
			&& ft_strcmp(flist->f->name, "./") != 0
			&& ft_strcmp(flist->f->name, "../") != 0
			&& S_ISDIR(flist->f->stat.st_mode))
			recursive_file(flist->f->path, flist->f->name, options);
		flist = flist->next;
	}
}

void	recursive_file(char *path, char *name, int options)
{
	t_dlist		*dlist;
	char		*pdup;
	char		*ndup;

	ft_putstr("\n");
	ft_putstr(path);
	ft_putstr(":\n");
	if (!(pdup = ft_strdup(path)))
		return ;
	if (!(ndup = ft_strdup(name)))
	{
		free(pdup);
		return ;
	}
	if (!(dlist = new_dlist(pdup, ndup, options)))
	{
		free(pdup);
		free(ndup);
		return ;
	}
	sort_dlist(dlist, options);
	print_dlist(dlist, NULL, options);
	delete_dlist(&dlist);
}
