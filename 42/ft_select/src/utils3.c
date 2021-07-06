/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 00:58:26 by pcharrie          #+#    #+#             */
/*   Updated: 2019/05/06 15:09:22 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_itolen(int n)
{
	int			i;
	long int	nb;

	nb = n;
	i = 0;
	if (nb < 0)
	{
		i++;
		nb = nb * -1;
	}
	if (nb == 0)
		i++;
	while (nb > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		signe;

	i = ft_itolen(n);
	if (!(str = (char *)malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	i--;
	signe = 1;
	if (n < 0)
	{
		str[0] = '-';
		signe = -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[i] = (n % 10) * signe + 48;
		n = n / 10;
		i--;
	}
	return (str);
}

int		ft_nblen(int n)
{
	int i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
