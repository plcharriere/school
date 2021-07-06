/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:17:40 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/25 20:09:56 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	push_flist(t_flist **flist, t_flist *flist2)
{
	flist2->next = *flist;
	*flist = flist2;
}

void	push_dlist(t_dlist **dlist, t_dlist *dlist2)
{
	dlist2->next = *dlist;
	*dlist = dlist2;
}
