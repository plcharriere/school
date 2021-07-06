/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:25:00 by marvin            #+#    #+#             */
/*   Updated: 2019/03/26 13:00:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_env
{
	struct s_env	*next;
	char			*name;
	char			*value;
}				t_env;

typedef struct	s_ms
{
	t_env	*env;
	int		exit_status;
}				t_ms;

typedef struct	s_ints
{
	int i;
	int j;
	int k;
}				t_ints;

int				builtin_cd_chdir(t_ms *ms, char *path);
int				builtin_cmd(char **command, t_ms *ms);
int				env_exists(t_env *env, char *name);
int				env_size(t_env *env);
int				main(int argc, char **argv, char **envp);
int				ms_env(t_ms *ms, char **env);
int				ms_env_cpy(t_env *ce, char *env);
int				splt_tb_sz(char c, char *str);
int				spz(char c, char *str, int index);
int				sp_str_tab_size(char *str);
int				spt_sz(char *str, int index);
int				ft_strlen(char *str);
int				ft_atoi(const char *str);
int				ft_strcmp(char *s1, char *s2);
int				tab_size(char **tab);
char			*env_get(t_env *env, char *name);
char			**env_toenvp(t_env *env);
char			**ft_str_split(char c, char *str);
char			**str_split_spacetab(char *str);
char			*ft_str_join(char *s1, char *s2);
char			*ft_strdup(char *str);
char			*ft_str_str_join(char *s1, char *s2, char *s3);
char			*ft_str_replace(char *find, char *in, char *replace);
char			*ft_strstr(char *haystack, char *needle);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			**env_toenvp(t_env *env);
char			**ft_str_split(char c, char *str);
char			**str_split_spacetab(char *str);
void			builtin_cd(char **command, t_ms *ms);
void			builtin_echo(char **command);
void			builtin_env_exec(char *command, char **envp, t_ms *ms);
void			builtin_env_i_destroy(t_env **nenv, char **tab, char **envp);
void			builtin_unsetenv(char **command, t_env **env);
void			builtin_exit(char **command, t_ms *ms);
void			builtin_env_i(char **command, t_ms *ms);
void			builtin_env(char **command, t_env *env, t_ms *ms);
void			builtin_setenv(char **command, t_env **env, t_ms *ms);
void			abs_cmd(char **command, t_ms *ms, char **envp);
void			path_exec(char *cmd_path, t_ms *ms, char **command);
void			path_cmd(char **command, t_ms *ms);
void			env_set(t_env **env, char *name, char *value);
void			env_edit(t_env *env, char *name, char *value);
void			env_add(t_env **env, char *name, char *value);
void			free_env(t_env *env);
void			env_remove(t_env **env, char *name);
void			env_setup(t_env **env);
void			error(char *s1, char *s2, int fatal);
void			error2(char *s1, char *s2, t_ms *ms);
void			error3(char *s1, char *s2, char *s3, t_ms *ms);
void			ms_vars_replace(char *name, t_env *env, char **tab);
void			ms_vars_set_env(t_env *env, char **tab);
void			ms_vars(t_env *env, char **tab);
void			ms_destroy(t_ms *ms);
void			env_destroy(t_env **env);
void			print_prompt(t_env *env);
void			print_path(t_env *env);
void			signal_setup(void);
void			signal_unsetup(void);
void			signal_ignore(void);
void			signal_print_prompt(t_ms *ms);
void			signal_sigint(int sig);
void			delete_string_tab(char **tab);
void			init_in(char **in, char c);
void			add_in(char **in, char c);
void			in_free(char **in, char *tmp);
void			read_stdin(t_ms *ms, char *in);
void			parse_commands(char *buf, t_ms *ms);
void			handle_command(char **command, t_ms *ms);
void			ft_putstr_fd(int fd, char *str);
void			ft_putstr(char *str);
void			double_free(void *s1, void *s2);
t_ms			*ms_new(char **env);

#endif
