/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 12:34:30 by marvin            #+#    #+#             */
/*   Updated: 2019/03/26 13:39:18 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_in(char **in, char c)
{
	if ((*in = (char *)malloc(sizeof(char) * 2)))
	{
		(*in)[0] = c;
		(*in)[1] = '\0';
	}
}

void	add_in(char **in, char c)
{
	char	*tmp;
	int		i;

	if (!(tmp = ft_strdup(*in)))
		return ;
	free(*in);
	if (!(*in = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 2))))
	{
		free(tmp);
		return ;
	}
	ft_strncpy(*in, tmp, ft_strlen(tmp));
	i = ft_strlen(tmp);
	(*in)[i++] = c;
	(*in)[i++] = '\0';
	free(tmp);
}

void	in_free(char **in, char *tmp)
{
	free(*in);
	*in = NULL;
	free(tmp);
}

void	read_stdin(t_ms *ms, char *in)
{
	char	buf[1];
	char	*tmp;

	while (read(0, buf, 1))
	{
		if (!in)
			init_in(&in, buf[0]);
		else
			add_in(&in, buf[0]);
		if (in[ft_strlen(in) - 1] == '\n')
		{
			tmp = ft_strdup(in);
			free(in);
			if (!tmp)
				return ;
			if (!(in = (char *)malloc(sizeof(char) * (ft_strlen(tmp)))))
				return (free(tmp));
			ft_strncpy(in, tmp, ft_strlen(tmp) - 1);
			in[ft_strlen(tmp) - 1] = '\0';
			parse_commands(in, ms);
			print_prompt(ms->env);
			in_free(&in, tmp);
		}
	}
}

void	parse_commands(char *buf, t_ms *ms)
{
	char **commands;
	char **command;
	char **tmp;

	commands = ft_str_split(';', buf);
	tmp = commands;
	while (*commands)
	{
		command = str_split_spacetab(*commands);
		ms_vars(ms->env, command);
		handle_command(command, ms);
		delete_string_tab(command);
		commands++;
	}
	delete_string_tab(tmp);
}
