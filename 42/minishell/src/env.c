/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 00:13:55 by marvin            #+#    #+#             */
/*   Updated: 2019/03/25 18:20:46 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int		env_exists(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (1);
		env = env->next;
	}
	return (0);
}

char	*env_get(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return ("");
}

void	env_set(t_env **env, char *name, char *value)
{
	if (!env_exists(*env, name))
		env_add(env, name, value);
	else
		env_edit(*env, name, value);
}

void	env_edit(t_env *env, char *name, char *value)
{
	int i;
	int j;

	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			free(env->value);
			j = ft_strlen(value) + 1;
			if (!(env->value = (char *)malloc(sizeof(char) * j)))
				return ;
			i = 0;
			while (value[i])
			{
				env->value[i] = value[i];
				i++;
			}
			env->value[i] = '\0';
			return ;
		}
		env = env->next;
	}
}

void	env_add(t_env **env, char *name, char *value)
{
	t_env *tmp;
	t_env *tmp2;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return ;
	tmp->next = NULL;
	if (!(tmp->name = ft_strdup(name)))
	{
		free(tmp);
		return ;
	}
	if (!(tmp->value = ft_strdup(value)))
	{
		double_free(tmp->name, tmp);
		return ;
	}
	if (!*env)
		*env = tmp;
	else
	{
		tmp2 = *env;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}
