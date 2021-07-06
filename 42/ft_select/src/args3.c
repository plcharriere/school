/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 22:13:34 by pcharrie          #+#    #+#             */
/*   Updated: 2019/08/26 22:14:59 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		args_init_loop(t_args **args, char **argv, t_args *tmp)
{
	(*args)->selected = 0;
	(*args)->cursor = 1;
	tmp = *args;
	while (*argv)
	{
		if (!(tmp->next = (t_args *)malloc(sizeof(t_args))))
		{
			args_destroy(args);
			return (0);
		}
		tmp = tmp->next;
		tmp->next = NULL;
		if (!(tmp->value = ft_strdup(*argv++)))
		{
			args_destroy(args);
			return (0);
		}
		tmp->selected = 0;
		tmp->cursor = 0;
	}
	return (1);
}
