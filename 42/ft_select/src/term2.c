/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 08:22:49 by pcharrie          #+#    #+#             */
/*   Updated: 2019/08/26 22:00:12 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	term_putnbr_nobuff(int n)
{
	char	*s;
	int		i;

	s = ft_itoa(n);
	i = 0;
	while (s[i])
		term_putchar_nobuff(s[i++]);
	free(s);
}

int		term_termcaps_working(void)
{
	if (!tgetstr("cl", NULL) || !tgetstr("kl", NULL) || !tgetstr("kr", NULL)
		|| !tgetstr("kb", NULL) || !tgetstr("kD", NULL) || !tgetstr("ku", NULL)
		|| !tgetstr("kd", NULL) || !tgetstr("cm", NULL) || !tgetstr("us", NULL)
		|| !tgetstr("mr", NULL) || !tgetstr("ue", NULL) || !tgetstr("me", NULL)
		|| !tgetstr("kh", NULL))
		return (0);
	return (1);
}
