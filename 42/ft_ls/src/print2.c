/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:13:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/20 18:29:55 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_flist_enoent(t_flist *flist)
{
	while (flist)
	{
		if (flist->f->errn)
			error_errn(flist->f->path, flist->f->errn, 0);
		flist = flist->next;
	}
}
