/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:18:24 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/28 17:41:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_flist(t_flist **flist, int options)
{
	if (*flist && (!(options & OPTION_MIN_F)))
	{
		if (options & OPTION_CAP_S)
			*flist = merge_sort(*flist, cmp_size);
		else if (options & OPTION_MIN_T)
		{
			if (options & OPTION_MIN_U)
				*flist = merge_sort(*flist, cmp_atime);
			else if (options & OPTION_CAP_U)
				*flist = merge_sort(*flist, cmp_birthtime);
			else if (options & OPTION_MIN_C)
				*flist = merge_sort(*flist, cmp_ctime);
			else
				*flist = merge_sort(*flist, cmp_mtime);
		}
		else
			*flist = merge_sort(*flist, cmp_name);
		if (options & OPTION_MIN_R)
			reverse_flist(flist);
	}
	if (options & OPTION_CAP_F)
		set_name_type(*flist);
	if (options & OPTION_MIN_P && !(options & OPTION_CAP_F))
		set_dir_slash(*flist);
	reverse_if_f(flist, options);
}

void	reverse_if_f(t_flist **flist, int options)
{
	if (options & OPTION_MIN_F)
		reverse_flist(flist);
}

void	sort_dlist(t_dlist *dlist, int options)
{
	while (dlist)
	{
		if (dlist->flist)
			sort_flist(&dlist->flist, options);
		dlist = dlist->next;
	}
}

void	reverse_flist(t_flist **flist)
{
	t_flist *current;
	t_flist *prev;
	t_flist *next;

	current = *flist;
	prev = NULL;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*flist = prev;
}
