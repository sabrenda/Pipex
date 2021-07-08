#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <string.h>
# include <getopt.h>
# include <errno.h>
# include <setjmp.h>
# include <signal.h>
# include <termios.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>

typedef struct s_monna
{
	t_list	*list;
	char	**tokens;
	char	**my_env;
	char	*tmp_env;
	int		fildes[2];
	int		fd_input;
	int		fd_output;
	int		flag_herodoc;
	int		flag_file;
	int		fd;
}			t_monna;

typedef struct s_any
{
	pid_t	pid;
	pid_t	wpid;
	char	*str;
	char	*tmp;
	char	**mas;
}			t_any;

typedef struct s_red_4
{
	char		*str;
	t_list		*tmp;
	int			fd;
}				t_red_4;

typedef struct s_copy_mass
{
	char		**str;
	int			j;
	int			tmp;
}				t_copy_mass;

int		ft_lenmassive(char **str);
void	ft_free_mass(char **mas);
void	ft_pipe_stdin(t_monna *lisa);
void	ft_pipe(t_monna *l, int i);
void	ft_any_argument(t_monna *lisa, int count);
void	ft_executor(t_monna *l);
void	ft_red_4_sup(t_red_4 *aa, t_monna *lisa, char *count);
void	ft_heredoc(t_monna *lisa);
void	ft_file(t_monna *lisa);
int		ft_init_env(t_monna *lisa, char **env);
int		ft_init_all(t_monna *lisa, char **env, int ac, char **av);
void	ft_list_clear(t_list **head);

#endif
