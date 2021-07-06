/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:46:11 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/11 19:46:20 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putchar(char c)
{
	char str[2];

	str[0] = c;
	str[1] = '\0';
	ft_putstr(str);
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(1, str);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *unsigned_s1;
	unsigned char *unsigned_s2;

	unsigned_s1 = (unsigned char *)s1;
	unsigned_s2 = (unsigned char *)s2;
	while (*unsigned_s1 == *unsigned_s2 && *unsigned_s1)
	{
		unsigned_s1++;
		unsigned_s2++;
	}
	return (*unsigned_s1 - *unsigned_s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(*str) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
