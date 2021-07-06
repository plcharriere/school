/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:28:31 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/28 17:07:37 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flist	*cut_half_flist(t_flist *flist)
{
	t_flist *fast;
	t_flist *slow;
	t_flist *prev;

	fast = flist;
	slow = flist;
	prev = NULL;
	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		prev = slow;
		slow = slow->next;
	}
	if (prev != NULL)
		prev->next = NULL;
	return (slow);
}

t_flist	*merge(t_flist *f1, t_flist *f2, int (*f)(t_flist *, t_flist *))
{
	t_flist tmp;
	t_flist *current;

	tmp.next = NULL;
	current = &tmp;
	while ((f1 != NULL) && (f2 != NULL))
	{
		if (f(f1, f2))
		{
			current->next = f1;
			f1 = f1->next;
		}
		else
		{
			current->next = f2;
			f2 = f2->next;
		}
		current = current->next;
	}
	current->next = f1 ? f1 : f2;
	return (tmp.next);
}

t_flist	*merge_sort(t_flist *flist, int (*f)(t_flist *, t_flist *))
{
	t_flist *flist1;
	t_flist *flist2;

	flist1 = flist;
	if (flist1 == NULL || flist1->next == NULL)
		return (flist1);
	flist2 = cut_half_flist(flist1);
	return (merge(merge_sort(flist1, f), merge_sort(flist2, f), f));
}
