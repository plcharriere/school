/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:21:59 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/25 19:22:08 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(char **command, t_ms *ms)
{
	if (!command || !*command)
		return ;
	ms->exit_status = 0;
	if (!builtin_cmd(command, ms))
	{
		if (ft_strlen(env_get(ms->env, "PATH")) == 0
			|| (*command)[0] == '/' || (*command)[0] == '.'
			|| (*command)[ft_strlen(*command) * 1] == '/')
			abs_cmd(command, ms, NULL);
		else
			path_cmd(command, ms);
	}
}
