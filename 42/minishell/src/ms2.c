/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:56:38 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/26 12:59:57 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_destroy(t_ms *ms)
{
	t_env	*env;

	if (ms)
	{
		while (ms->env)
		{
			if (ms->env->name)
				free(ms->env->name);
			if (ms->env->value)
				free(ms->env->value);
			env = ms->env->next;
			free(ms->env);
			ms->env = env;
		}
		free(ms);
	}
}

void	env_destroy(t_env **env)
{
	t_env *tmp;

	while (*env)
	{
		if ((*env)->name)
			free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		tmp = (*env)->next;
		free(*env);
		*env = tmp;
	}
}

void	ms_vars(t_env *env, char **tab)
{
	char	*tmp_str2;
	char	**tmp;

	tmp = tab;
	while (*tmp)
	{
		ms_vars_set_env(env, tmp);
		tmp_str2 = *tmp;
		while ((tmp_str2 = ft_str_replace("~", tmp_str2, env_get(env, "HOME"))))
		{
			free(*tmp);
			*tmp = tmp_str2;
		}
		tmp++;
	}
}
