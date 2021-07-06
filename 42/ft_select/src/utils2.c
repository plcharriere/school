/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 00:58:26 by pcharrie          #+#    #+#             */
/*   Updated: 2019/05/06 14:21:57 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*ft_strdup(char *s)
{
	char	*new;
	int		i;

	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (*s)
		new[i++] = *s++;
	new[i] = '\0';
	return (new);
}

void	ft_bzero(void *buf, int size)
{
	int		i;
	char	*buf_cast;

	buf_cast = (char *)buf;
	i = 0;
	while (i < size)
		buf_cast[i++] = 0;
}

int		ft_strcmp(char *s1, char *s2)
{
	unsigned char *us1;
	unsigned char *us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 == *us2 && *us1)
	{
		us1++;
		us2++;
	}
	return (*us1 - *us2);
}

void	ft_putwhitespaces(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		term_putchar(' ');
		i++;
	}
}

char	*getextension(char *s)
{
	int		len;

	len = ft_strlen(s) - 1;
	while (len >= 0 && s[len] != '.')
		len--;
	if (len < 0)
		return (NULL);
	return (s + len);
}
