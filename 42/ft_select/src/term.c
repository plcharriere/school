/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:23:57 by pcharrie          #+#    #+#             */
/*   Updated: 2019/05/06 15:10:31 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	term_setup(struct termios *term)
{
	(*term).c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	tputs(tgetstr("ks", NULL), 1, term_putchar_nobuff);
	tputs(tgetstr("vi", NULL), 1, term_putchar_nobuff);
}

void	term_unsetup(struct termios *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	tputs(tgetstr("ve", NULL), 1, term_putchar_nobuff);
	tputs(tgetstr("cl", NULL), 1, term_putchar_nobuff);
}

int		term_putchar(int c)
{
	static char	buff[4096];
	static int	i = 0;

	buff[i] = c;
	i++;
	if (c == '\n' || i == 4095)
	{
		buff[i] = '\0';
		ft_putstr_fd(0, buff);
		i = 0;
	}
	return (unsigned char)c;
}

int		term_putchar_nobuff(int c)
{
	ft_putchar_fd(0, c);
	return (unsigned char)c;
}

void	term_putnbr(int n)
{
	char	*s;
	int		i;

	s = ft_itoa(n);
	i = 0;
	while (s[i])
		term_putchar(s[i++]);
	free(s);
}
