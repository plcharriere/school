/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:05:40 by marvin            #+#    #+#             */
/*   Updated: 2019/03/25 19:46:56 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		splt_tb_sz(char c, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str != c)
			i = 1;
		if (*str == c && i == 1)
		{
			j++;
			i = 0;
		}
		str++;
	}
	if (i == 1)
		j++;
	return (j);
}

int		spz(char c, char *str, int index)
{
	int i;

	i = 0;
	while (str[index] && str[index] != c)
	{
		i++;
		index++;
	}
	return (i);
}

char	**ft_str_split(char c, char *str)
{
	char	**tab;
	t_ints	t;

	if (!(tab = (char **)malloc(sizeof(char *) * (splt_tb_sz(c, str) + 1))))
		return (NULL);
	t.i = 0;
	t.k = 0;
	while (str[t.k])
	{
		while (str[t.k] == c)
			t.k++;
		if (!str[t.k])
			break ;
		if (!(tab[t.i] = (char *)malloc(sizeof(char) * (spz(c, str, t.k) + 1))))
		{
			delete_string_tab(tab);
			return (NULL);
		}
		t.j = 0;
		while (str[t.k] && str[t.k] != c)
			tab[t.i][t.j++] = str[t.k++];
		tab[t.i++][t.j] = '\0';
	}
	tab[t.i] = NULL;
	return (tab);
}

void	delete_string_tab(char **tab)
{
	char **tmp;

	tmp = tab;
	if (tab)
	{
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(tab);
		tab = NULL;
	}
}
