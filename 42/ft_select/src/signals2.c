/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 22:00:39 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/05 09:32:49 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	signals_resize(t_args **a)
{
	static t_args		**args = NULL;

	if (a)
		args = a;
	else if (args)
	{
		tputs(tgetstr("cl", NULL), 1, term_putchar);
		print_args(*args);
	}
}

void	signals_winch(int signum)
{
	(void)signum;
	signals_resize(NULL);
}

void	signals_tstp(int signum)
{
	(void)signum;
	signals_suspend(NULL);
	signal(SIGTSTP, SIG_DFL);
}

void	signals_suspend(struct termios *t)
{
	static struct termios	*term = NULL;

	if (term)
	{
		tputs(tgetstr("cl", NULL), 1, term_putchar);
		term_unsetup(term);
	}
	else if (t)
		term = t;
}
