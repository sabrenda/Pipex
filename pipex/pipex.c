#include "pipex.h"

void	ft_file(t_monna *lisa)
{
	int	fd;

	fd = open(lisa->tokens[0], O_RDONLY);
	dup2(fd, 0);
	close(fd);
	lisa->flag_file = 1;
}

int	ft_init_env(t_monna *lisa, char **env)
{
	int	i;

	i = 0;
	ft_bzero(lisa, sizeof(t_monna));
	lisa->my_env = (char **)malloc(sizeof(char *) * (ft_lenmassive(env) + 1));
	if (!lisa->my_env)
		return (0);
	lisa->my_env[ft_lenmassive(env)] = NULL;
	lisa->tmp_env = (char *)malloc(sizeof(char) * 300);
	if (!lisa->tmp_env)
		return (0);
	while (env[i])
	{
		lisa->my_env[i] = ft_strdup(env[i]);
		if (!(lisa->my_env[i]))
			return (0);
		i++;
	}
	lisa->my_env[i] = NULL;
	return (1);
}

int	ft_init_all(t_monna *lisa, char **env, int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_bzero(lisa, sizeof(t_monna));
	if (ft_init_env(lisa, env) == 0)
		return (0);
	lisa->tokens = (char **)malloc(sizeof(char *) * ac);
	if (!lisa->tokens)
		return (0);
	while (av[++i])
	{
		lisa->tokens[j] = ft_strdup(av[i]);
		if (!(lisa->tokens[j]))
			return (0);
		j++;
	}
	lisa->tokens[j] = NULL;
	lisa->fd_input = dup(0);
	lisa->fd_output = dup(1);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_monna		lisa;
	int			i;

	if (argc < 5)
	{
		write(1, "wrong size arguments\n", 21);
		return (0);
	}
	if (ft_strcmp("here_doc", argv[1]) && access(argv[1], 0) == -1)
	{
		ft_putstr_fd("no such file or directory: ", 1);
		ft_putendl_fd(argv[1], 1);
		return (0);
	}
	if (!(ft_init_all(&lisa, env, argc, argv)))
		return (0);
	if (ft_strcmp("here_doc", argv[1]) == 0)
		ft_heredoc(&lisa);
	else
		ft_file(&lisa);
	ft_executor(&lisa);
	dup2(lisa.fd_input, 0);
	dup2(lisa.fd_output, 1);
	return (0);
}
