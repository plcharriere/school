/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:06:52 by pcharrie          #+#    #+#             */
/*   Updated: 2019/08/26 22:01:14 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	keys_remove_args(t_args **args, t_args *prev, t_args *cur, t_args *next)
{
	prev = NULL;
	cur = *args;
	if (cur)
		next = cur->next;
	while (cur)
	{
		if (cur->cursor)
		{
			if (prev)
				prev->next = next;
			else
				*args = next;
			if (next)
				next->cursor = 1;
			else if (prev)
				prev->cursor = 1;
			args_free(cur);
			return ;
		}
		prev = cur;
		cur = next;
		if (next)
			next = next->next;
	}
}

void	keys_search_input(t_args **args, char c)
{
	static char	buf[4096];
	static int	i = 4096;
	int			j;
	t_args		*tmp;

	if (i == 4096)
	{
		i = 0;
		ft_bzero(buf, 4096);
	}
	buf[i] = c;
	tmp = *args;
	while (tmp)
	{
		j = i;
		while (ft_strcmp(buf + j, tmp->value) && j >= 0)
			j--;
		if (!ft_strcmp(buf + j, tmp->value))
		{
			args_cursorbyarg(*args, tmp);
			return ;
		}
		tmp = tmp->next;
	}
	i++;
}

void	keys_home(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		if (tmp->cursor == 1)
			tmp->cursor = 0;
		tmp = tmp->next;
	}
	(*args)->cursor = 1;
}

void	keys_end(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		if (tmp->cursor == 1)
			tmp->cursor = 0;
		if (!tmp->next)
			tmp->cursor = 1;
		tmp = tmp->next;
	}
}
