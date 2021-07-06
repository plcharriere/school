/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flist_linebreak.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:11:33 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/11 22:56:08 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_flist_linebreak(t_flist *flist, int options)
{
	while (flist)
	{
		print_file_name(flist->f, options);
		ft_putstr("\n");
		flist = flist->next;
	}
}
