/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:25:50 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 22:06:13 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	delete_clean_flist(t_flist **flist)
{
	t_flist *list;

	while (*flist)
	{
		list = (*flist)->next;
		free(*flist);
		*flist = list;
	}
}

int		get_clean_flist_push(t_flist **new, t_flist **next, t_flist *flist)
{
	if (!*new)
	{
		if (!(*new = (t_flist *)malloc(sizeof(t_flist))))
			return (0);
		(*new)->f = flist->f;
		(*new)->next = NULL;
		*next = *new;
	}
	else
	{
		if (!((*next)->next = (t_flist *)malloc(sizeof(t_flist))))
		{
			delete_clean_flist(new);
			return (0);
		}
		*next = (*next)->next;
		(*next)->f = flist->f;
		(*next)->next = NULL;
	}
	return (1);
}

t_flist	*get_clean_flist(t_flist *flist)
{
	t_flist *new;
	t_flist *next;

	new = NULL;
	while (flist)
	{
		if (flist->f->errn == 0)
		{
			if (!get_clean_flist_push(&new, &next, flist))
				return (NULL);
		}
		flist = flist->next;
	}
	return (new);
}

int		print_flist(t_flist *flist, int options, int total)
{
	struct termios	term;
	t_flist			*clean_flist;

	if (!(clean_flist = get_clean_flist(flist)))
		return (1);
	if (options & OPTION_MIN_L)
		print_flist_long(clean_flist, options, total);
	else if (!(options & OPTION_ONE) && tcgetattr(1, &term) == 0)
		print_flist_cols(clean_flist, clean_flist, options);
	else
		print_flist_linebreak(clean_flist, options);
	if (options & OPTION_CAP_R && !(options & OPTION_MIN_D))
		recursive_flist(clean_flist, options);
	delete_clean_flist(&clean_flist);
	return (1);
}

void	print_dlist(t_dlist *dlist, t_flist *flist, int options)
{
	if (dlist->next || flist)
	{
		while (dlist)
		{
			ft_putstr(dlist->path);
			ft_putstr(":\n");
			if (dlist->errn == 0)
				print_flist(dlist->flist, options, 1);
			else
				error_errn(dlist->name, dlist->errn, 0);
			if (dlist->next)
				ft_putstr("\n");
			dlist = dlist->next;
		}
	}
	else
	{
		if (dlist->errn == 0)
			print_flist(dlist->flist, options, 1);
		else
			error_errn(dlist->name, dlist->errn, 0);
	}
}
