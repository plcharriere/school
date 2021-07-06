/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:23:23 by pcharrie          #+#    #+#             */
/*   Updated: 2019/08/26 22:16:00 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		args_init(t_args **args, char **argv, t_args *tmp)
{
	if (!(*args = (t_args *)malloc(sizeof(t_args))))
		return (0);
	(*args)->next = NULL;
	if (!((*args)->value = ft_strdup(*argv++)))
	{
		args_destroy(args);
		return (0);
	}
	return (args_init_loop(args, argv, tmp));
}

void	args_destroy(t_args **args)
{
	t_args *tmp;

	if (args)
	{
		while (*args)
		{
			if ((*args)->value)
				free((*args)->value);
			tmp = (*args)->next;
			free(*args);
			*args = tmp;
		}
	}
}

void	args_free(t_args *args)
{
	if (args)
	{
		if (args->value)
			free(args->value);
		free(args);
	}
}

int		args_len(t_args *args)
{
	int i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}

int		args_maxlen(t_args *args)
{
	int i;

	i = 0;
	while (args)
	{
		if (ft_strlen(args->value) > i)
			i = ft_strlen(args->value);
		args = args->next;
	}
	return (i);
}
