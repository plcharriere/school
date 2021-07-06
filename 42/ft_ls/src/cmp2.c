/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:11:23 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 19:33:44 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_birthtime(t_flist *flist1, t_flist *flist2)
{
	if (flist1->f->stat.st_birthtime == flist2->f->stat.st_birthtime)
	{
		return (ft_strcmp(flist1->f->name, flist2->f->name) < 0);
	}
	else
		return (flist1->f->stat.st_birthtime > flist2->f->stat.st_birthtime);
}
