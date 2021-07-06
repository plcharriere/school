/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 23:39:26 by pcharrie          #+#    #+#             */
/*   Updated: 2019/08/26 22:06:57 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		print_getcols(t_args *args)
{
	int				cols;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	cols = args_len(args);
	while (cols > 1 && args_maxlen(args) > w.ws_col / cols - 1)
		cols--;
	return (cols);
}

int		print_getrows(t_args *args)
{
	int cols;
	int rows;

	cols = print_getcols(args);
	rows = args_len(args) / cols;
	if (args_len(args) % cols)
		rows++;
	return (rows);
}

void	print_header(void)
{
	struct winsize	w;
	int				i;
	char			*s;

	s = " FT_SELECT ";
	ioctl(0, TIOCGWINSZ, &w);
	i = 0;
	while (i < (w.ws_col - ft_strlen(s)) / 2)
	{
		tputs("─", 1, term_putchar);
		i++;
	}
	tputs(s, 1, term_putchar);
	i = 0;
	while (i < (w.ws_col - ft_strlen(s)) / 2)
	{
		tputs("─", 1, term_putchar);
		i++;
	}
	if (!(w.ws_col % 2))
		tputs("─", 1, term_putchar);
	tputs("\n", 1, term_putchar);
}

void	print_footer(t_args *args)
{
	struct winsize	w;
	int				i;
	char			*s;

	ioctl(0, TIOCGWINSZ, &w);
	tputs(tgoto(tgetstr("cm", NULL), 0, w.ws_row - 2), 1, term_putchar);
	i = -1;
	while (++i < w.ws_col)
		tputs("─", 1, term_putchar);
	tputs("\n", 1, term_putchar);
	tputs("Selected : ", 1, term_putchar_nobuff);
	term_putnbr_nobuff(args_selectedlen(args));
	tputs("/", 1, term_putchar_nobuff);
	term_putnbr_nobuff(args_len(args));
	s = "ARROWS : Move | SPACE : Select | ENTER : Confirm | DEL/BACKSPACE : \
	Delete | ESC : Quit";
	if (w.ws_col > ft_strlen("Selected : / ")
		+ ft_nblen(args_len(args) + ft_nblen(args_selectedlen(args)))
		+ ft_strlen(s))
		print_footer_tputs(w, s);
}

int		print_enoughspace(t_args *args, int cols, int rows)
{
	struct winsize	w;

	(void)cols;
	ioctl(0, TIOCGWINSZ, &w);
	if (w.ws_row < rows + 3 || w.ws_col < args_maxlen(args) || w.ws_col < 13
		|| w.ws_col <= (ft_strlen("Selected : /") + ft_nblen(args_len(args)
			+ ft_nblen(args_selectedlen(args)))))
		return (0);
	return (1);
}
