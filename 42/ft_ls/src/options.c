/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:53:52 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/28 17:39:07 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	is_char_valid_option(char c)
{
	char	*valid_options;
	int		i;

	valid_options = "AFGRSTUacdfgloprtu1";
	i = 0;
	while (valid_options[i])
	{
		if (valid_options[i] == c)
			return ;
		i++;
	}
	ft_putstr_fd(2, "ft_ls: illegal option -- ");
	ft_putchar_fd(2, c);
	ft_putstr_fd(2, "\nusage: ls [-");
	ft_putstr_fd(2, valid_options);
	ft_putstr_fd(2, "] [file ...]\n");
	exit(1);
}

void	parse_char_options(char c, int *options)
{
	is_char_valid_option(c);
	if (c == 'T')
		*options = *options | OPTION_CAP_T;
	if (c == 'l')
		*options = *options | OPTION_MIN_L;
	if (c == 'R')
		*options = *options | OPTION_CAP_R;
	if (c == 'a')
		*options = *options | OPTION_MIN_A;
	if (c == 'r')
		*options = *options | OPTION_MIN_R;
	if (c == 't')
		*options = *options | OPTION_MIN_T;
	if (c == 'u')
		*options = (*options | OPTION_MIN_U) & ~OPTION_CAP_U & ~OPTION_MIN_C;
	if (c == 'f')
		*options = *options | OPTION_MIN_F | OPTION_MIN_A;
	if (c == 'g')
		*options = *options | OPTION_MIN_G | OPTION_MIN_L;
	if (c == 'd')
		*options = *options | OPTION_MIN_D;
	if (c == 'p')
		*options = (*options | OPTION_MIN_P) & ~OPTION_CAP_F;
	parse_char_options_next(c, options);
}

void	parse_char_options_next(char c, int *options)
{
	if (c == 'o')
		*options = *options | OPTION_MIN_O | OPTION_MIN_L;
	if (c == 'd')
		*options = *options | OPTION_MIN_D;
	if (c == 'G')
		*options = *options | OPTION_CAP_G;
	if (c == 'U')
		*options = (*options | OPTION_CAP_U) & ~OPTION_MIN_U & ~OPTION_MIN_C;
	if (c == 'c')
		*options = (*options | OPTION_MIN_C) & ~OPTION_CAP_U & ~OPTION_MIN_U;
	if (c == 'S')
		*options = *options | OPTION_CAP_S;
	if (c == 'F')
		*options = *options | OPTION_CAP_F;
	if (c == 'A')
		*options = *options | OPTION_CAP_A;
	if (c == '1')
		*options = (*options | OPTION_ONE) & ~OPTION_MIN_L;
}
