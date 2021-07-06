/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:18:22 by marvin            #+#    #+#             */
/*   Updated: 2019/03/25 19:20:18 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_ms	*ms;
	int		status;

	(void)argc;
	(void)argv;
	if (!(ms = ms_new(envp)))
		error("malloc", "Cannot allocate memory", 1);
	env_setup(&(ms->env));
	signal_print_prompt(ms);
	signal_setup();
	print_prompt(ms->env);
	read_stdin(ms, NULL);
	status = ms->exit_status;
	ms_destroy(ms);
	return (status);
}
