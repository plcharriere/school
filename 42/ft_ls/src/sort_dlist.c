/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 21:28:14 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/11 19:48:38 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_dlist_flist(t_dlist *dlist1, t_dlist *dlist2)
{
	t_flist	*flist;
	char	*path;

	flist = dlist1->flist;
	path = dlist1->path;
	dlist1->flist = dlist2->flist;
	dlist1->path = dlist2->path;
	dlist2->flist = flist;
	dlist2->path = path;
}

void	sort_dlist_path(t_dlist *dlist)
{
	t_dlist *dlist1;
	t_dlist *dlist2;

	dlist1 = dlist;
	while (dlist1)
	{
		dlist2 = dlist;
		while (dlist2)
		{
			if (ft_strcmp(dlist1->path, dlist2->path) < 0)
				swap_dlist_flist(dlist1, dlist2);
			dlist2 = dlist2->next;
		}
		dlist1 = dlist1->next;
	}
}
