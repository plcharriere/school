/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:19:21 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/25 18:47:16 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_setup(void)
{
	signal(SIGINT, signal_sigint);
}

void	signal_unsetup(void)
{
	signal(SIGINT, SIG_DFL);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
}

void	signal_print_prompt(t_ms *ms)
{
	static t_ms	*static_ms;

	if (ms)
		static_ms = ms;
	else
	{
		ft_putstr("\n");
		print_prompt(static_ms->env);
	}
}

void	signal_sigint(int sig)
{
	(void)sig;
	signal_print_prompt(NULL);
}
