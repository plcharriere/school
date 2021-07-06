/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:12:29 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/25 17:32:39 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
	}
}

void	env_remove(t_env **env, char *name)
{
	t_env *prev;
	t_env *current;
	t_env *next;

	prev = NULL;
	current = *env;
	if (current)
		next = current->next;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
		{
			if (prev)
				prev->next = next;
			else
				*env = next;
			free_env(current);
			return ;
		}
		prev = current;
		current = next;
		if (next)
			next = next->next;
	}
}

int		env_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_toenvp(t_env *env)
{
	char	**envp;
	int		i;

	if (!(envp = (char **)malloc(sizeof(char *) * (env_size(env) + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (!(envp[i++] = ft_str_str_join(env->name, "=", env->value)))
		{
			delete_string_tab(envp);
			return (NULL);
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	env_setup(t_env **env)
{
	char buff[8192];

	if (!ft_strlen(env_get(*env, "PWD")))
	{
		getcwd(buff, 8192);
		env_set(env, "PWD", buff);
	}
}
