/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 09:13:59 by pcharrie          #+#    #+#             */
/*   Updated: 2019/04/18 21:48:51 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	error2(char *s1, char *s2)
{
	ft_putstr_fd(2, s1);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, s2);
	ft_putstr_fd(2, "\n");
}

void	error3(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(2, s1);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, s2);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, s3);
	ft_putstr_fd(2, "\n");
}
