/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_cols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:25:12 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/27 18:07:04 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_flist_columns2(t_flist *flist, t_col *col, t_colints ints, int op)
{
	t_flist		*list;

	while (++ints.j < col->nbrows)
	{
		ints.i = -1;
		ints.k = 0;
		while (++ints.i < col->nbcols)
		{
			if (!(list = get_flist_index(flist, ints.k + ints.l, 0)))
			{
				++ints.i;
				continue;
			}
			print_file_name(list->f, op);
			if (ints.i + 1 < col->nbcols)
				ft_put_whitespaces(col->max - ft_strlen(list->f->name));
			ints.k = ints.k + col->nbrows;
		}
		ft_putstr("\n");
		ints.l++;
	}
	get_flist_index(NULL, 0, 1);
}

void	print_flist_cols(t_flist *flist, t_flist *list, int options)
{
	struct winsize	w;
	t_col			col;
	t_colints		ints;

	col.max = 8;
	col.nbfiles = 0;
	while (list)
	{
		while (col.max <= ft_strlen(list->f->name))
			col.max = (options & OPTION_CAP_G ? col.max + 4 : col.max + 8);
		list = list->next;
		col.nbfiles++;
	}
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col.nbcols = w.ws_col / col.max;
	if (col.nbfiles % col.nbcols != 0)
		col.nbrows = col.nbfiles / col.nbcols + 1;
	else
		col.nbrows = col.nbfiles / col.nbcols;
	ints.j = -1;
	ints.l = 0;
	print_flist_columns2(flist, &col, ints, options);
}
