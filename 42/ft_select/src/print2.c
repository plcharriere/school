/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 23:39:26 by pcharrie          #+#    #+#             */
/*   Updated: 2019/08/26 22:04:47 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_keys_usage(void)
{
	tputs(tgetstr("mr", NULL), 1, term_putchar_nobuff);
	tputs("ARROWS", 1, term_putchar_nobuff);
	tputs(tgetstr("me", NULL), 1, term_putchar_nobuff);
	tputs(" : Move | ", 1, term_putchar_nobuff);
	tputs(tgetstr("mr", NULL), 1, term_putchar_nobuff);
	tputs("SPACE", 1, term_putchar_nobuff);
	tputs(tgetstr("me", NULL), 1, term_putchar_nobuff);
	tputs(" : Select | ", 1, term_putchar_nobuff);
	tputs(tgetstr("mr", NULL), 1, term_putchar_nobuff);
	tputs("ENTER", 1, term_putchar_nobuff);
	tputs(tgetstr("me", NULL), 1, term_putchar_nobuff);
	tputs(" : Confirm | ", 1, term_putchar_nobuff);
	tputs(tgetstr("mr", NULL), 1, term_putchar_nobuff);
	tputs("DEL", 1, term_putchar_nobuff);
	tputs(tgetstr("me", NULL), 1, term_putchar_nobuff);
	tputs("/", 1, term_putchar_nobuff);
	tputs(tgetstr("mr", NULL), 1, term_putchar_nobuff);
	tputs("BACKSPACE", 1, term_putchar_nobuff);
	tputs(tgetstr("me", NULL), 1, term_putchar_nobuff);
	tputs(" : Delete | ", 1, term_putchar_nobuff);
	tputs(tgetstr("mr", NULL), 1, term_putchar_nobuff);
	tputs("ESC", 1, term_putchar_nobuff);
	tputs(tgetstr("me", NULL), 1, term_putchar_nobuff);
	tputs(" : Quit", 1, term_putchar_nobuff);
}

void	print_cols(t_args *args, int ws_col, int cols, int rows)
{
	int		i;
	int		j;
	int		k;
	t_args	*curr;

	i = -1;
	k = 0;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if ((curr = args_getbyindex(args, k)))
			{
				args_printvalue(curr);
				ft_putwhitespaces(ws_col / cols - ft_strlen(curr->value));
			}
			k++;
		}
		term_putchar('\n');
	}
}

void	print_args(t_args *args)
{
	struct winsize	w;
	int				cols;
	int				rows;

	ioctl(0, TIOCGWINSZ, &w);
	cols = print_getcols(args);
	rows = print_getrows(args);
	if (!print_enoughspace(args, cols, rows))
	{
		tputs("NOT ENOUGH SPACE\n", 1, term_putchar);
		return ;
	}
	print_header();
	print_cols(args, w.ws_col, cols, rows);
	print_footer(args);
}

void	print_footer_tputs(struct winsize w, char *s)
{
	char *tgoto1;

	tgoto1 = tgoto(tgetstr("cm", NULL), w.ws_col - ft_strlen(s), w.ws_row - 1);
	tputs(tgoto1, 1, term_putchar_nobuff);
	print_keys_usage();
}
