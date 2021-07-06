/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 08:38:19 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/05 09:19:04 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	keys_catch2(char *bf, t_args **args)
{
	if (ft_strlen(bf) == 1 && bf[0] == 32)
	{
		keys_select_args(*args);
		keys_move_args_right(*args);
	}
	else if (!ft_strcmp(bf, tgetstr("kl", NULL)))
		keys_move_args_left(*args);
	else if (!ft_strcmp(bf, tgetstr("kr", NULL)))
		keys_move_args_right(*args);
	else if (!ft_strcmp(bf, tgetstr("kh", NULL)))
		keys_home(args);
	else if (ft_strlen(bf) == 3 && bf[0] == 27 && bf[1] == 79 && bf[2] == 70)
		keys_end(args);
	else if (!ft_strcmp(bf, tgetstr("kb", NULL))
		|| !ft_strcmp(bf, tgetstr("kD", NULL))
		|| (ft_strlen(bf) == 1 && bf[0] == 127))
		keys_remove_args(args, NULL, NULL, NULL);
	else if (!ft_strcmp(bf, tgetstr("ku", NULL)))
		keys_move_args_up(*args);
	else if (!ft_strcmp(bf, tgetstr("kd", NULL)))
		keys_move_args_down(*args);
	else if (ft_strlen(bf) == 1 && ((bf[0] >= 'a' && bf[0] <= 'z')
		|| (bf[0] >= 'A' && bf[0] <= 'Z') || bf[0] == '_'
		|| bf[0] == '.' || bf[0] == '/' || bf[0] == ' '))
		keys_search_input(args, bf[0]);
}

void	keys_catch(t_args **args)
{
	char	buf[5];

	ft_bzero(buf, 5);
	while (read(STDIN_FILENO, &buf, 5) > 0)
	{
		if (ft_strlen(buf) == 1 && buf[0] == 10)
			return ;
		else if (ft_strlen(buf) == 1 && (buf[0] == 27 || buf[0] == 4))
			return (args_destroy(args));
		else
			keys_catch2(buf, args);
		if (!*args)
			return ;
		tputs(tgetstr("cl", NULL), 1, term_putchar);
		print_args(*args);
		ft_bzero(buf, 5);
	}
}

void	return_selected_args(t_args *args)
{
	t_args *tmp;

	tmp = NULL;
	while (args)
	{
		if (!tmp && args->selected)
			tmp = args;
		if (args->selected && args != tmp)
			ft_putstr(" ");
		if (args->selected)
			ft_putstr(args->value);
		args = args->next;
	}
}

void	ft_select(t_args **args, struct termios term, struct termios oterm)
{
	signals_setup();
	term_setup(&term);
	signals_quit(args, &oterm);
	signals_resize(args);
	signals_suspend(&term);
	signals_unsuspend(&term, args);
	tputs(tgetstr("cl", NULL), 1, term_putchar);
	print_args(*args);
	keys_catch(args);
	term_unsetup(&oterm);
	return_selected_args(*args);
	args_destroy(args);
}

int		main(int argc, char **argv)
{
	char			*termname;
	struct termios	term;
	t_args			*args;

	if (!isatty(0))
		error2("ft_select", "not in a terminal");
	else if (!(termname = getenv("TERM")))
		error2("ft_select", "environment variable TERM not set");
	else if (tgetent(NULL, termname) < 1)
		error2("ft_select", "could not find term entry");
	else if (tcgetattr(STDIN_FILENO, &term) == -1)
		error2("ft_select", "tcgetattr error");
	else if (!term_termcaps_working())
		error2("ft_select", "some caps are not avalaible for TERM variable");
	else if (argc < 2)
		ft_putstr("ft_select: usage: ft_select args...\n");
	else if (!args_init(&args, ++argv, NULL))
		error2("ft_select", "cannot allocate memory");
	else
	{
		ft_select(&args, term, term);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
