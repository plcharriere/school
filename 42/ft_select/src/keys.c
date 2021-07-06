/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 00:10:51 by pcharrie          #+#    #+#             */
/*   Updated: 2019/05/09 17:17:08 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	keys_move_args_right(t_args *args)
{
	t_args *tmp;

	tmp = args;
	while (tmp)
	{
		if (tmp->cursor && tmp->next)
		{
			tmp->cursor = 0;
			tmp->next->cursor = 1;
			return ;
		}
		if (!tmp->next)
		{
			tmp->cursor = 0;
			args->cursor = 1;
		}
		tmp = tmp->next;
	}
}

void	keys_move_args_left(t_args *args)
{
	t_args *prev;

	prev = NULL;
	while (args)
	{
		if (args->cursor && prev)
		{
			args->cursor = 0;
			prev->cursor = 1;
			return ;
		}
		else if (args->cursor && !prev)
		{
			args->cursor = 0;
			while (args->next)
				args = args->next;
			args->cursor = 1;
			return ;
		}
		prev = args;
		args = args->next;
	}
}

void	keys_move_args_up(t_args *args)
{
	int				i;
	t_args			*tmp_args;

	i = 0;
	tmp_args = args;
	while (tmp_args)
	{
		if (tmp_args->cursor)
		{
			tmp_args->cursor = 0;
			break ;
		}
		i++;
		tmp_args = tmp_args->next;
	}
	if ((tmp_args = args_getbyindex(args, i - print_getcols(args))))
		tmp_args->cursor = 1;
	else
	{
		while (i < args_len(args) - print_getcols(args))
			i += print_getcols(args);
		if ((tmp_args = args_getbyindex(args, i)))
			tmp_args->cursor = 1;
	}
}

void	keys_move_args_down(t_args *args)
{
	int				i;
	t_args			*tmp_args;

	i = 0;
	tmp_args = args;
	while (tmp_args)
	{
		if (tmp_args->cursor)
		{
			tmp_args->cursor = 0;
			break ;
		}
		i++;
		tmp_args = tmp_args->next;
	}
	if ((tmp_args = args_getbyindex(args, i + print_getcols(args))))
		tmp_args->cursor = 1;
	else
	{
		while (i >= print_getcols(args))
			i -= print_getcols(args);
		if ((tmp_args = args_getbyindex(args, i)))
			tmp_args->cursor = 1;
	}
}

void	keys_select_args(t_args *args)
{
	while (args)
	{
		if (args->cursor)
			args->selected = !args->selected;
		args = args->next;
	}
}
