/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:18:47 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/05 09:33:50 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	signals_setup(void)
{
	signal(SIGINT, signals_sigint);
	signal(SIGQUIT, signals_sigint);
	signal(SIGABRT, signals_sigint);
	signal(SIGKILL, signals_sigint);
	signal(SIGTERM, signals_sigint);
	signal(SIGCONT, signals_cont);
	signal(SIGWINCH, signals_winch);
}

void	signals_sigint(int signum)
{
	(void)signum;
	signals_quit(NULL, NULL);
}

void	signals_cont(int signum)
{
	(void)signum;
	signals_unsuspend(NULL, NULL);
}

void	signals_quit(t_args **a, struct termios *t)
{
	static t_args			**args = NULL;
	static struct termios	*term = NULL;

	if (args && term)
	{
		term_unsetup(term);
		args_destroy(args);
		exit(0);
	}
	else if (a && t)
	{
		args = a;
		term = t;
	}
}

void	signals_unsuspend(struct termios *t, t_args **a)
{
	static struct termios	*term = NULL;
	static t_args			**args = NULL;

	if (term && args)
	{
		term_setup(term);
		signal(SIGTSTP, signals_tstp);
		tputs(tgetstr("cl", NULL), 1, term_putchar);
		print_args(*args);
		keys_catch(args);
	}
	else if (t && a)
	{
		term = t;
		args = a;
	}
}
