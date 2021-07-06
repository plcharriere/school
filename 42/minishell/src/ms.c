/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:13:42 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/26 13:37:28 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*ms_new(char **env)
{
	t_ms *ms;

	if (!(ms = (t_ms *)malloc(sizeof(t_ms))))
	{
		ms_destroy(ms);
		return (NULL);
	}
	ms->env = NULL;
	ms->exit_status = 0;
	if (!ms_env(ms, env))
	{
		ms_destroy(ms);
		return (NULL);
	}
	return (ms);
}

int		ms_env(t_ms *ms, char **env)
{
	t_env *tmp;
	t_env *tmp2;

	while (*env)
	{
		if (!(tmp = (t_env *)malloc(sizeof(t_env))) || !ms_env_cpy(tmp, *env))
			return (0);
		tmp->next = NULL;
		if (!ms->env)
			ms->env = tmp;
		else
		{
			tmp2 = ms->env;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->next = tmp;
		}
		env++;
	}
	return (1);
}

int		ms_env_cpy(t_env *ce, char *env)
{
	int	i;
	int j;

	ce->name = NULL;
	ce->value = NULL;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!(ce->name = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		ce->name[i] = env[i];
		i++;
	}
	ce->name[i++] = '\0';
	if (!(ce->value = (char *)malloc(sizeof(char) * (ft_strlen(env) - i + 1))))
		return (0);
	j = 0;
	while (i < ft_strlen(env))
		ce->value[j++] = env[i++];
	ce->value[j] = '\0';
	return (1);
}

void	ms_vars_replace(char *name, t_env *env, char **tab)
{
	char *str3;
	char *s4;

	if ((str3 = ft_str_join("$", name)))
	{
		s4 = *tab;
		while ((s4 = ft_str_replace(str3, s4, env_get(env, name))))
		{
			free(*tab);
			*tab = s4;
		}
		free(str3);
	}
}

void	ms_vars_set_env(t_env *env, char **tab)
{
	char	*str2;
	char	name[4096];
	int		i;

	str2 = *tab;
	i = 0;
	while (*str2)
	{
		if (*str2++ == '$')
		{
			while (((*str2 >= 'a' && *str2 <= 'z')
				|| (*str2 >= 'A' && *str2 <= 'Z') || *str2 == '_') && i < 4095)
				name[i++] = *str2++;
			name[i++] = '\0';
			if (i > 0)
				ms_vars_replace(name, env, tab);
			return (ms_vars_set_env(env, tab));
		}
	}
}
