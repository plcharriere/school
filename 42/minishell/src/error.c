/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:15:32 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/24 20:04:53 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *s1, char *s2, int fatal)
{
	ft_putstr_fd(2, s1);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, s2);
	ft_putstr_fd(2, "\n");
	if (fatal)
		exit(EXIT_FAILURE);
}

void	error2(char *s1, char *s2, t_ms *ms)
{
	ft_putstr_fd(2, s1);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, s2);
	ft_putstr_fd(2, "\n");
	ms->exit_status = EXIT_FAILURE;
}

void	error3(char *s1, char *s2, char *s3, t_ms *ms)
{
	ft_putstr_fd(2, s1);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, s2);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, s3);
	ft_putstr_fd(2, "\n");
	ms->exit_status = EXIT_FAILURE;
}
