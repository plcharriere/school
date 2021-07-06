/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:16:54 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/26 22:06:17 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_flist_passwd_group(t_f *f)
{
	struct passwd	*passwd;
	struct group	*group;

	passwd = getpwuid(f->stat.st_uid);
	if (!passwd || !(f->passwd.pw_name = ft_strdup(passwd->pw_name)))
		f->passwd.pw_name = NULL;
	group = getgrgid(f->stat.st_gid);
	if (!group || !(f->group.gr_name = ft_strdup(group->gr_name)))
		f->group.gr_name = NULL;
}

t_flist	*new_flist(char *name, char *path)
{
	t_flist			*flist;

	if (!(flist = (t_flist *)malloc(sizeof(t_flist))))
		return (NULL);
	if (!(flist->f = (t_f *)malloc(sizeof(t_f))))
	{
		free(flist);
		return (NULL);
	}
	flist->next = NULL;
	flist->f->name = name;
	flist->f->path = path;
	flist->f->errn = 0;
	if (stat(path, &(flist->f->stat)) == -1
	&& readlink(flist->f->path, NULL, 0) == -1)
	{
		flist->f->passwd.pw_name = ft_strdup("");
		flist->f->group.gr_name = ft_strdup("");
		flist->f->errn = errno;
		return (flist);
	}
	if (readlink(flist->f->path, NULL, 0) > -1)
		lstat(flist->f->path, &(flist->f->stat));
	set_flist_passwd_group(flist->f);
	return (flist);
}

t_dlist	*new_dlist(char *path, char *name, int options)
{
	t_dlist *dlist;
	t_flist *flist;

	if (!(dlist = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	dlist->next = NULL;
	dlist->path = path;
	dlist->name = name;
	dlist->errn = 0;
	dlist->flist = NULL;
	flist = NULL;
	if (!(open_dir(dlist, options, flist)))
	{
		free(dlist);
		return (NULL);
	}
	return (dlist);
}
