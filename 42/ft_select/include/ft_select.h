/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 08:37:47 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/05 09:21:21 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include <stdlib.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

# define COLOR_RESET  "\x1B[0m"
# define COLOR_RED  "\x1B[31m"
# define COLOR_GREEN  "\x1B[32m"
# define COLOR_YELLOW  "\x1B[33m"
# define COLOR_BLUE  "\x1B[34m"
# define COLOR_MAGENTA  "\x1B[35m"
# define COLOR_CYAN  "\x1B[36m"
# define COLOR_WHITE  "\x1B[37m"

# define COLOR_RESET  "\x1B[0m"
# define COLOR_BOLD_RED  "\x1B[1;31m"
# define COLOR_BOLD_GREEN  "\x1B[1;32m"
# define COLOR_BOLD_YELLOW  "\x1B[1;33m"
# define COLOR_BOLD_BLUE  "\x1B[1;34m"
# define COLOR_BOLD_MAGENTA  "\x1B[1;35m"
# define COLOR_BOLD_CYAN  "\x1B[1;36m"
# define COLOR_BOLD_WHITE  "\x1B[1;37m"

typedef struct	s_args
{
	struct s_args	*next;
	char			*value;
	int				selected;
	int				cursor;
}				t_args;

void			ft_putchar_fd(int fd, char c);
void			ft_putchar(char c);
void			ft_putstr_fd(int fd, char *s);
void			ft_putstr(char *s);
int				ft_strlen(char *s);
char			*ft_strdup(char *s);
void			ft_bzero(void *buf, int size);
int				ft_strcmp(char *s1, char *s2);
void			ft_putwhitespaces(int n);
char			*getextension(char *s);
char			*ft_itoa(int n);
int				ft_nblen(int n);

void			term_setup(struct termios *term);
void			term_unsetup(struct termios *term);
int				term_putchar(int c);
int				term_putchar_nobuff(int c);
void			term_putnbr(int n);
void			term_putnbr_nobuff(int n);
int				term_termcaps_working(void);

void			keys_catch(t_args **args);

void			signals_setup(void);
void			signals_sigint(int signum);
void			signals_quit(t_args **a, struct termios *t);
void			signals_cont(int signum);
void			signals_tstp(int signum);
void			signals_suspend(struct termios *t);
void			signals_unsuspend(struct termios *t, t_args **a);
void			signals_resize(t_args **a);
void			signals_winch(int signum);

int				args_init(t_args **args, char **argv, t_args *tmp);
int				args_init_loop(t_args **args, char **argv, t_args *tmp);
void			args_destroy(t_args **args);
void			args_free(t_args *args);
int				args_len(t_args *args);
int				args_selectedlen(t_args *args);
int				args_maxlen(t_args *args);
t_args			*args_getbyindex(t_args *args, int index);
void			args_printvalue(t_args *args);
void			args_printvaluecolor(t_args *args);
void			args_cursorbyarg(t_args *args, t_args *toselect);

int				print_getcols(t_args *args);
int				print_getrows(t_args *args);
void			print_args(t_args *args);
void			print_keys_usage(void);
void			print_header(void);
void			print_footer(t_args *args);
void			print_footer_tputs(struct winsize w, char *s);
int				print_enoughspace(t_args *args, int cols, int rows);

void			keys_move_args_left(t_args *args);
void			keys_move_args_right(t_args *args);
void			keys_move_args_up(t_args *args);
void			keys_move_args_down(t_args *args);
void			keys_select_args(t_args *args);
void			keys_remove_args(t_args **a, t_args *p, t_args *c, t_args *n);
void			keys_search_input(t_args **args, char c);
void			keys_home(t_args **args);
void			keys_end(t_args **args);

void			error2(char *s1, char *s2);
void			error3(char *s1, char *s2, char *s3);

#endif
