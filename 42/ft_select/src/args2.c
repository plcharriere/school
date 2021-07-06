/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:37:59 by pcharrie          #+#    #+#             */
/*   Updated: 2019/05/06 15:17:37 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_args	*args_getbyindex(t_args *args, int index)
{
	int i;

	i = 0;
	while (args)
	{
		if (i == index)
			return (args);
		i++;
		args = args->next;
	}
	return (args);
}

void	args_printvalue(t_args *args)
{
	if (!args)
		return ;
	args_printvaluecolor(args);
	if (args->cursor)
		tputs(tgetstr("us", NULL), 1, term_putchar);
	if (args->selected)
		tputs(tgetstr("mr", NULL), 1, term_putchar);
	tputs(args->value, 1, term_putchar);
	if (args->cursor)
		tputs(tgetstr("ue", NULL), 1, term_putchar);
	if (args->selected)
		tputs(tgetstr("me", NULL), 1, term_putchar);
	tputs(COLOR_RESET, 1, term_putchar);
}

void	args_printvaluecolor(t_args *args)
{
	char	*ext;

	ext = getextension(args->value);
	if (ext && !ft_strcmp(ext, ".c"))
		tputs(COLOR_GREEN, 1, term_putchar);
	else if (ext && !ft_strcmp(ext, ".o"))
		tputs(COLOR_BOLD_BLUE, 1, term_putchar);
	else if (ext && !ft_strcmp(ext, ".cpp"))
		tputs(COLOR_BOLD_GREEN, 1, term_putchar);
	else if (ext && !ft_strcmp(ext, ".h"))
		tputs(COLOR_BOLD_MAGENTA, 1, term_putchar);
	else if (!ft_strcmp(args->value, "Makefile"))
		tputs(COLOR_BOLD_RED, 1, term_putchar);
	else if (!ft_strcmp(args->value, "auteur"))
		tputs(COLOR_YELLOW, 1, term_putchar);
}

void	args_cursorbyarg(t_args *args, t_args *toselect)
{
	while (args)
	{
		if (args == toselect)
			args->cursor = 1;
		else
			args->cursor = 0;
		args = args->next;
	}
}

int		args_selectedlen(t_args *args)
{
	int i;

	i = 0;
	while (args)
	{
		if (args->selected)
			i++;
		args = args->next;
	}
	return (i);
}
