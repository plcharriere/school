/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 12:32:50 by marvin            #+#    #+#             */
/*   Updated: 2019/03/24 19:33:23 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_env *env)
{
	ft_putstr("\x1b[32m");
	ft_putstr("minishell");
	ft_putstr("\x1b[0m");
	ft_putstr(":");
	ft_putstr("\x1b[36m");
	print_path(env);
	ft_putstr("\x1b[0m");
	ft_putstr("$ ");
}

void	print_path(t_env *env)
{
	char *home;
	char *pwd;

	home = env_get(env, "HOME");
	pwd = env_get(env, "PWD");
	while (*home == *pwd && *home)
	{
		home++;
		pwd++;
	}
	if (!*home)
		ft_putstr("~");
	else
		pwd = env_get(env, "PWD");
	ft_putstr(pwd);
}
