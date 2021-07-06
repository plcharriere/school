/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 23:49:22 by marvin            #+#    #+#             */
/*   Updated: 2019/03/26 13:08:22 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	abs_cmd(char **command, t_ms *ms, char **envp)
{
	struct stat	buf;
	int			pid;

	if (stat(*command, &buf) == -1)
		error2(*command, "No such file or directory", ms);
	else if (access(*command, F_OK | X_OK) == -1 || S_ISDIR(buf.st_mode)
		|| !S_ISREG(buf.st_mode))
		error2(*command, "permission denied", ms);
	else
	{
		if (!(envp = env_toenvp(ms->env)))
			return ;
		pid = fork();
		if (pid < 0)
			error2("fork", "error", ms);
		if (!pid)
		{
			signal_unsetup();
			execve(*command, command, envp);
		}
		signal_ignore();
		waitpid(pid, NULL, 0);
		signal_setup();
		delete_string_tab(envp);
	}
}

void	path_exec(char *cmd_path, t_ms *ms, char **command)
{
	char	**envp;
	int		pid;

	if (access(cmd_path, X_OK) != -1)
	{
		if (!(envp = env_toenvp(ms->env)))
			return ;
		pid = fork();
		if (pid < 0)
			error2("fork", "error", ms);
		if (!pid)
		{
			signal_unsetup();
			execve(cmd_path, command, envp);
		}
		signal_ignore();
		wait(NULL);
		delete_string_tab(envp);
		signal_setup();
		free(cmd_path);
	}
	else
		error2(*command, "Permission denied", ms);
}

void	path_cmd(char **command, t_ms *ms)
{
	char	**path;
	int		i;
	char	*cmd_path;

	if (!(path = ft_str_split(':', env_get(ms->env, "PATH"))))
		return ;
	i = 0;
	while (path[i])
	{
		if (!(cmd_path = ft_str_str_join(path[i], "/", *command)))
			return ;
		if (access(cmd_path, F_OK) != -1)
		{
			path_exec(cmd_path, ms, command);
			delete_string_tab(path);
			return ;
		}
		free(cmd_path);
		i++;
	}
	delete_string_tab(path);
	error2(*command, "command not found", ms);
}

int		builtin_cmd(char **command, t_ms *ms)
{
	if (!ft_strcmp(*command, "cd"))
		builtin_cd(command, ms);
	else if (!ft_strcmp(*command, "echo"))
		builtin_echo(command);
	else if (!ft_strcmp(*command, "env"))
		builtin_env(command, ms->env, ms);
	else if (!ft_strcmp(*command, "setenv"))
		builtin_setenv(command, &ms->env, ms);
	else if (!ft_strcmp(*command, "unsetenv"))
		builtin_unsetenv(command, &ms->env);
	else if (!ft_strcmp(*command, "exit"))
		builtin_exit(command, ms);
	else
		return (0);
	return (1);
}
