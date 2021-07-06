/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:06:16 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/25 20:35:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unsetenv(char **command, t_env **env)
{
	command++;
	if (!*command)
		error("unsetenv: usage", "unsetenv NAME", 0);
	while (*command)
		env_remove(env, *command++);
}

void	builtin_exit(char **command, t_ms *ms)
{
	int status;

	command++;
	if (*command && *(command + 1))
		error("exit", "Too many arguments", 0);
	else
	{
		if (*command)
		{
			status = ft_atoi(*command);
			if (ft_strcmp(*command, "0") && !status)
				status = EXIT_FAILURE;
		}
		else
			status = ms->exit_status;
		ms_destroy(ms);
		exit(status);
	}
}

void	builtin_env_i(char **command, t_ms *ms)
{
	t_env	*nenv;
	char	**tab;
	char	**envp;

	nenv = NULL;
	envp = NULL;
	tab = NULL;
	while (*command)
	{
		if (!(tab = ft_str_split('=', *command)))
			return (builtin_env_i_destroy(&nenv, tab, envp));
		if (tab_size(tab) > 1)
			env_set(&nenv, tab[0], tab[1]);
		else
		{
			if (!(envp = env_toenvp(nenv)))
				return (builtin_env_i_destroy(&nenv, tab, envp));
			builtin_env_exec(tab[0], envp, ms);
			builtin_env_i_destroy(&nenv, tab, envp);
			return ;
		}
		delete_string_tab(tab);
		command++;
	}
	env_destroy(&nenv);
}

void	builtin_env(char **command, t_env *env, t_ms *ms)
{
	if (*(command + 1) && !(ft_strcmp(*++command, "-i")))
		builtin_env_i(++command, ms);
	else
	{
		while (env)
		{
			ft_putstr(env->name);
			ft_putstr("=");
			ft_putstr(env->value);
			ft_putstr("\n");
			env = env->next;
		}
	}
}

void	builtin_setenv(char **command, t_env **env, t_ms *ms)
{
	char *name;
	char *value;

	command++;
	if (!(name = *command))
	{
		builtin_env(command, *env, ms);
		return ;
	}
	command++;
	if (!(value = *command++))
	{
		error("setenv: usage", "setenv NAME value", 0);
		return ;
	}
	env_set(env, name, value);
}
