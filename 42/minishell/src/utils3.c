/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:16:41 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/25 19:51:30 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

void	double_free(void *s1, void *s2)
{
	free(s1);
	free(s2);
}

int		tab_size(char **tab)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = tab;
	while (*tmp)
	{
		i++;
		tmp++;
	}
	return (i);
}
