/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:26:26 by pcharrie          #+#    #+#             */
/*   Updated: 2019/03/24 19:52:47 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sp_str_tab_size(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			i = 1;
		if ((*str == ' ' || *str == '\t') && i == 1)
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

int		spt_sz(char *str, int index)
{
	int i;

	i = 0;
	while (str[index] && str[index] != ' ' && str[index] != '\t')
	{
		i++;
		index++;
	}
	return (i);
}

char	**str_split_spacetab(char *str)
{
	char	**tab;
	t_ints	t;

	if (!(tab = (char **)malloc(sizeof(char *) * (sp_str_tab_size(str) + 1))))
		return (NULL);
	t.i = 0;
	t.k = 0;
	while (str[t.k])
	{
		while (str[t.k] == ' ' || str[t.k] == '\t')
			t.k++;
		if (!str[t.k])
			break ;
		if (!(tab[t.i] = (char *)malloc(sizeof(char) * (spt_sz(str, t.k) + 1))))
		{
			delete_string_tab(tab);
			return (NULL);
		}
		t.j = 0;
		while (str[t.k] && str[t.k] != ' ' && str[t.k] != '\t')
			tab[t.i][t.j++] = str[t.k++];
		tab[t.i++][t.j] = '\0';
	}
	tab[t.i] = NULL;
	return (tab);
}
