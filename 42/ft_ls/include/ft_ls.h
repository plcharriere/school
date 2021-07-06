/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:55:32 by pcharrie          #+#    #+#             */
/*   Updated: 2019/02/28 17:08:10 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include <time.h>
# include <errno.h>
# include <termios.h>

enum			e_options
{
	OPTION_MIN_L = 0x1,
	OPTION_CAP_R = 0x2,
	OPTION_MIN_A = 0x4,
	OPTION_MIN_R = 0x8,
	OPTION_MIN_T = 0x10,
	OPTION_MIN_U = 0x20,
	OPTION_MIN_F = 0x40,
	OPTION_MIN_G = 0x80,
	OPTION_MIN_D = 0x100,
	OPTION_ONE = 0x200,
	OPTION_CAP_T = 0x400,
	OPTION_MIN_P = 0x800,
	OPTION_MIN_O = 0x1000,
	OPTION_CAP_G = 0x2000,
	OPTION_CAP_U = 0x4000,
	OPTION_MIN_C = 0x8000,
	OPTION_CAP_S = 0x10000,
	OPTION_CAP_F = 0x20000,
	OPTION_CAP_A = 0x40000
};

typedef struct	s_dlist
{
	struct s_dlist	*next;
	char			*name;
	char			*path;
	int				errn;
	struct s_flist	*flist;
}				t_dlist;

typedef struct	s_flist
{
	struct s_flist	*next;
	struct s_f		*f;
}				t_flist;

typedef struct	s_f
{
	char			*name;
	char			*path;
	int				errn;
	struct stat		stat;
	struct stat		lstat;
	struct passwd	passwd;
	struct group	group;
}				t_f;

typedef struct	s_col
{
	int		max;
	int		nbcols;
	int		nbfiles;
	int		nbrows;
}				t_col;

typedef struct	s_colints
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
}				t_colints;

typedef struct	s_longmaxs
{
	int		nlink_max;
	int		username_max;
	int		groupname_max;
	int		size_max;
	int		sizespecial_max;
}				t_longmaxs;

int				cmp_name(t_flist *flist1, t_flist *flist2);
int				cmp_size(t_flist *flist1, t_flist *flist2);
int				cmp_mtime(t_flist *flist1, t_flist *flist2);
int				cmp_atime(t_flist *flist1, t_flist *flist2);
int				cmp_ctime(t_flist *flist1, t_flist *flist2);
int				cmp_birthtime(t_flist *flist1, t_flist *flist2);
int				delete_flist(t_flist **flist);
int				delete_dlist(t_dlist **dlist);
void			error_errn(char *str, int errn, int fatal);
int				flist_has_valid(t_flist *flist);
int				print_flist_dlist(t_flist *flist, t_dlist *dlist, int options);
void			set_flist_passwd_group(t_f *f);
t_flist			*new_flist(char *name, char *path);
t_dlist			*new_dlist(char *path, char *name, int options);
int				set_name(char **file_path, char **tmp, char *dpath, char *enm);
int				set_name2(char **file_path, char **name, char *entryname);
int				set_dlist(t_flist **f, t_flist **t, char **fp, char **name);
int				open_dir(t_dlist *dlist, int options, t_flist *tmpflist);
void			is_char_valid_option(char c);
void			parse_char_options(char c, int *options);
void			parse_char_options_next(char c, int *options);
int				parse_argv(char ***argv, int *opts, t_flist **f, t_dlist **d);
void			parse_argv_options(char ***argv, int *options);
int				parse_push_dlist(t_dlist **d, char *a1, char *a2, int options);
int				parse_push_flist(char **av, char *a1, char *a2, t_flist **fl);
int				parse_argv_files_dir(char **a, t_flist **f, t_dlist **d, int o);
void			print_flist_columns2(t_flist *f, t_col *c, t_colints i, int o);
void			print_flist_cols(t_flist *flist, t_flist *list, int options);
void			print_flist_linebreak(t_flist *flist, int options);
void			print_file_date1(char *str);
void			print_file_date2(char *str);
void			print_file_date3(char *str);
void			print_file_date(t_f *f, int options);
int				get_nlink_max(t_flist *flist);
int				get_username_max(t_flist *flist);
int				get_groupname_max(t_flist *flist);
int				get_file_size_max(t_flist *flist);
int				get_file_specialsize_max(t_flist *flist);
void			print_file_size_special(t_f *f, int max);
void			print_file_size(t_f *f, int max);
void			print_file_name_long(t_f *f, int options);
void			print_file_permissions(t_f *f);
void			print_file_xattr(t_f *f);
void			print_file_nlink(t_f *f, int max);
void			print_file_username(t_f *f, int max);
void			print_file_groupname(t_f *f, int max);
void			print_file_permissions(t_f *f);
void			print_file_xattr(t_f *f);
void			print_file_nlink(t_f *f, int max);
void			print_file_username(t_f *f, int max);
void			print_file_groupname(t_f *f, int max);
void			print_flist_long2(t_flist *list, int options, t_longmaxs *maxs);
void			print_flist_long(t_flist *flist, int options, int total);
void			print_flist_total(t_flist *flist);
void			print_file_name2(t_f *f);
void			print_file_name(t_f *f, int options);
void			print_file_type_permissions(t_f *f);
void			delete_clean_flist(t_flist **flist);
int				get_clean_flist_push(t_flist **n, t_flist **next, t_flist *f);
t_flist			*get_clean_flist(t_flist *flist);
int				print_flist(t_flist *flist, int options, int total);
void			print_dlist(t_dlist *dlist, t_flist *flist, int options);
void			print_flist_enoent(t_flist *flist);
void			push_flist(t_flist **flist, t_flist *flist2);
void			push_dlist(t_dlist **dlist, t_dlist *dlist2);
void			recursive_flist(t_flist *flist, int options);
void			recursive_file(char *path, char *name, int options);
void			swap_dlist_flist(t_dlist *dlist1, t_dlist *dlist2);
void			sort_dlist_path(t_dlist *dlist);
void			sort_flist(t_flist **flist, int options);
void			sort_dlist(t_dlist *dlist, int options);
void			reverse_if_f(t_flist **flist, int options);
void			reverse_flist(t_flist **flist);
t_flist			*cut_half_flist(t_flist *flist);
t_flist			*merge(t_flist *a, t_flist *b, int (*f)(t_flist *, t_flist *));
t_flist			*merge_sort(t_flist *flist, int (*f)(t_flist *, t_flist *));
void			ft_put_whitespaces(int n);
void			ft_putchar_fd(int fd, char c);
void			ft_putstr_fd(int fd, char *str);
int				double_char_free(char *s1, char *s2);
int				flist_len(t_flist *flist);
char			*ft_strdup(char *src);
int				ft_nblen(int n);
void			ft_putnbr(int n);
int				ft_itolen(int n);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char *str);
int				ft_strlen(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin(char *s1, char *s2);
t_flist			*get_flist_index(t_flist *flist, int index, int reset);
void			set_name_type(t_flist *flist);
void			set_dir_slash(t_flist *flist);

#endif
