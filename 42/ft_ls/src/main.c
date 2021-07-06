/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:51:06 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 19:12:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		flist_has_valid(t_flist *flist)
{
	while (flist)
	{
		if (flist->f->errn == 0)
			return (1);
		flist = flist->next;
	}
	return (0);
}

int		print_flist_dlist(t_flist *flist, t_dlist *dlist, int options)
{
	flist = merge_sort(flist, cmp_name);
	print_flist_enoent(flist);
	sort_flist(&flist, options);
	sort_dlist(dlist, options);
	if (flist)
	{
		if (!(print_flist(flist, options, 0)))
			return (0);
		if (dlist && flist_has_valid(flist))
			ft_putstr("\n");
	}
	if (dlist)
		print_dlist(dlist, flist, options);
	delete_flist(&flist);
	delete_dlist(&dlist);
	return (0);
}

int		main(int argc, char **argv)
{
	int		options;
	t_flist	*flist;
	t_dlist	*dlist;

	argv++;
	(void)argc;
	if (!parse_argv(&argv, &options, &flist, &dlist))
		return (0);
	return (print_flist_dlist(flist, dlist, options));
}
