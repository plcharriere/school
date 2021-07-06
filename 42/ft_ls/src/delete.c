/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:15:42 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/27 21:57:47 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		delete_flist(t_flist **flist)
{
	t_flist *tmp;

	while (*flist)
	{
		free((*flist)->f->name);
		free((*flist)->f->path);
		free((*flist)->f->passwd.pw_name);
		free((*flist)->f->group.gr_name);
		free((*flist)->f);
		tmp = (*flist)->next;
		free(*flist);
		*flist = tmp;
	}
	return (0);
}

int		delete_dlist(t_dlist **dlist)
{
	t_dlist *tmp;

	while (*dlist)
	{
		free((*dlist)->path);
		free((*dlist)->name);
		delete_flist(&((*dlist)->flist));
		tmp = (*dlist)->next;
		free(*dlist);
		*dlist = tmp;
	}
	return (0);
}
