/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 02:41:04 by marvin            #+#    #+#             */
/*   Updated: 2020/03/10 11:50:03 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd_chdir(t_ms *ms, char *path)
{
	char		buff[8192];
	struct stat	buf;

	if (stat(path, &buf) < 0)
		error3("cd", path, "No such file or directory", ms);
	else if (!S_ISDIR(buf.st_mode))
		error3("cd", path, "Not a directory", ms);
	else if (access(path, X_OK) == -1)
		error3("cd", path, "Permission denied", ms);
	else if (chdir(path) < 0)
	{
		ft_putstr_fd(2, "cd: error\n");
		ms->exit_status = EXIT_FAILURE;
	}
	else
	{
		env_set(&ms->env, "OLDPWD", env_get(ms->env, "PWD"));
		getcwd(buff, 8192);
		env_set(&ms->env, "PWD", buff);
		return (1);
	}
	return (0);
}

void	builtin_cd(char **command, t_ms *ms)
{
	char *oldpwd;
	char *t;

	if (!*++command || !ft_strcmp(*command, "--"))
		builtin_cd_chdir(ms, env_get(ms->env, "HOME"));
	else if (!ft_strcmp(*command, "-"))
	{
		if (!(oldpwd = ft_strdup(env_get(ms->env, "OLDPWD"))))
			return ;
		if (builtin_cd_chdir(ms, env_get(ms->env, "OLDPWD")))
		{
			t = oldpwd;
			while ((t = ft_str_replace(env_get(ms->env, "HOME"), t, "~")))
			{
				free(oldpwd);
				oldpwd = t;
			}
			ft_putstr(oldpwd);
			ft_putstr("\n");
		}
		free(oldpwd);
	}
	else
		builtin_cd_chdir(ms, *command);
}

void	builtin_echo(char **command)
{
	int	a;

	command++;
	a = 0;
	if (*command && !ft_strcmp(*command, "-n"))
	{
		a = 1;
		command++;
	}
	while (*command)
	{
		ft_putstr(*command);
		command++;
		if (*command)
			ft_putstr(" ");
	}
	if (!a)
		ft_putstr("\n");
}

void	builtin_env_exec(char *command, char **envp, t_ms *ms)
{
	struct stat	buf;
	int			pid;

	if (stat(command, &buf) == -1)
		error2(command, "No such file or directory", ms);
	else if (access(command, F_OK | X_OK) == -1 || S_ISDIR(buf.st_mode)
		|| !S_ISREG(buf.st_mode))
		error2(command, "permission denied", ms);
	else
	{
		pid = fork();
		if (pid)
		{
			waitpid(pid, NULL, 0);
			pid = 0;
		}
		else if (!pid)
			execve(command, NULL, envp);
	}
}

void	builtin_env_i_destroy(t_env **nenv, char **tab, char **envp)
{
	env_destroy(nenv);
	delete_string_tab(tab);
	delete_string_tab(envp);
}
