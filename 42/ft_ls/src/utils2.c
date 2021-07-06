/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:45:40 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/11 19:46:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strdup(char *src)
{
	char	*str;
	int		i;

	if (!(str = (char *)malloc(sizeof(*str) * (ft_strlen(src) + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
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

void	ft_putnbr(int n)
{
	if (n == 2147483647)
	{
		ft_putnbr(214748364);
		ft_putnbr(7);
		return ;
	}
	if (n == -2147483648)
	{
		ft_putnbr(-214748364);
		ft_putnbr(8);
		return ;
	}
	if (n < 0)
	{
		ft_putstr("-");
		n = n * -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + 48);
}

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
