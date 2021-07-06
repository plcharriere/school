/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:03:40 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/28 17:39:11 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parse_argv(char ***argv, int *opts, t_flist **flist, t_dlist **dlist)
{
	*opts = 0;
	*flist = NULL;
	*dlist = NULL;
	parse_argv_options(argv, opts);
	if (!(**argv))
	{
		if (*opts & OPTION_MIN_D)
		{
			if (!(*flist = new_flist(ft_strdup("."), ft_strdup("."))))
				return (0);
		}
		else if (!(*dlist = new_dlist(ft_strdup("."), ft_strdup("."), *opts)))
			return (0);
	}
	else
	{
		if (!parse_argv_files_dir(*argv, flist, dlist, *opts))
		{
			delete_flist(flist);
			delete_dlist(dlist);
			return (0);
		}
		sort_dlist_path(*dlist);
	}
	return (1);
}

void	parse_argv_options(char ***argv, int *options)
{
	*options = 0;
	while (**argv && ***argv == '-' && ft_strlen(**argv) > 1)
	{
		if (ft_strcmp(**argv, "--") == 0)
		{
			(*argv)++;
			return ;
		}
		(**argv)++;
		while (***argv)
		{
			parse_char_options(***argv, options);
			(**argv)++;
		}
		(*argv)++;
	}
}

int		parse_push_dlist(t_dlist **dlist, char *avdp1, char *avdp2, int options)
{
	t_dlist	*tmpdlist;

	if (!*dlist)
	{
		if (!(*dlist = new_dlist(avdp1, avdp2, options)))
		{
			double_char_free(avdp1, avdp2);
			return (0);
		}
	}
	else
	{
		if (!(tmpdlist = new_dlist(avdp1, avdp2, options)))
		{
			double_char_free(avdp1, avdp2);
			return (0);
		}
		push_dlist(dlist, tmpdlist);
	}
	return (1);
}

int		parse_push_flist(char **argv, char *avdp1, char *avdp2, t_flist **flist)
{
	t_flist	*tmpflist;

	if (!ft_strcmp(*argv, ""))
	{
		error_errn("ft_ls: open", 0, 0);
		return (double_char_free(avdp1, avdp2));
	}
	else if (!*flist)
	{
		if (!(*flist = new_flist(avdp1, avdp2)))
			return (double_char_free(avdp1, avdp2));
	}
	else
	{
		if (!(tmpflist = new_flist(avdp1, avdp2)))
			return (double_char_free(avdp1, avdp2));
		push_flist(flist, tmpflist);
	}
	return (1);
}

int		parse_argv_files_dir(char **av, t_flist **flst, t_dlist **dlst, int op)
{
	struct stat	buf;
	char		*argvdup1;
	char		*argvdup2;

	while (*av)
	{
		if (!(argvdup1 = ft_strdup(*av))
			|| !(argvdup2 = ft_strdup(*av)))
			return (0);
		if (stat(*av, &buf) == 0 && ((S_ISDIR(buf.st_mode)
			&& readlink(*av, NULL, 0) == -1)
			|| (S_ISDIR(buf.st_mode) && !(op & OPTION_MIN_L)))
			&& !(op & OPTION_MIN_D))
		{
			if (!parse_push_dlist(dlst, argvdup1, argvdup2, op))
				return (0);
		}
		else
		{
			if (!(parse_push_flist(av, argvdup1, argvdup2, flst)))
				return (0);
		}
		av++;
	}
	return (1);
}
