/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:26:32 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/28 17:39:04 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_errn(char *str, int errn, int fatal)
{
	if (!errn)
	{
		ft_putstr_fd(2, "ft_ls: ");
		ft_putstr_fd(2, str);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, strerror(errno));
		ft_putstr_fd(2, "\n");
	}
	else
	{
		ft_putstr_fd(2, "ft_ls: ");
		ft_putstr_fd(2, str);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, strerror(errn));
		ft_putstr_fd(2, "\n");
	}
	if (fatal)
		exit(0);
}
