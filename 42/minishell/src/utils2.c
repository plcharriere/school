/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:28:29 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/25 16:46:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_str_join(char *s1, char *s2, char *s3)
{
	char *tmp;
	char *str;

	if (!(tmp = ft_str_join(s1, s2)))
		return (NULL);
	str = ft_str_join(tmp, s3);
	free(tmp);
	return (str);
}

char	*ft_str_replace(char *find, char *in, char *replace)
{
	char	*found;
	char	*str;
	t_ints	ints;

	if ((found = ft_strstr(in, find)) && in != NULL)
	{
		ints.k = ft_strlen(in) - ft_strlen(find) + ft_strlen(replace) + 1;
		if ((str = (char *)malloc(sizeof(char) * ints.k)))
		{
			ints.i = 0;
			while (in != found)
				str[ints.i++] = *in++;
			ints.j = 0;
			while (ints.j++ < ft_strlen(find))
				in++;
			while (*replace)
				str[ints.i++] = *replace++;
			while (*in)
				str[ints.i++] = *in++;
			str[ints.i] = '\0';
			return (str);
		}
	}
	return (NULL);
}

int		ft_atoi(const char *str)
{
	long long	n;
	int			signe;

	n = 0;
	signe = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (n < 0)
		return (signe == -1 ? 0 : -1);
	return (n * signe);
}

int		ft_strcmp(char *s1, char *s2)
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

char	*ft_strstr(char *haystack, char *needle)
{
	int i;
	int j;
	int k;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = i;
		k = 0;
		while (haystack[j])
		{
			if (haystack[j] == needle[k])
				k++;
			else
				k = 0;
			j++;
			if (needle[k] == '\0')
				return ((char *)(haystack + j - ft_strlen(needle)));
		}
		i++;
	}
	return (NULL);
}
