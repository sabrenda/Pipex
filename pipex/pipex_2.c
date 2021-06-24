#include "pipex.h"

void ft_any_argument(t_monna *lisa, int count)
{
	t_any any;

	any.mas = ft_split(lisa->tokens[count], ' ');
	any.str = ft_strjoin("/bin/", any.mas[0]);
	any.pid = fork();
	if (any.pid == 0)
	{
		if (execve(any.str, any.mas, lisa->my_env) == -1)
			printf("pipex: %s: command not found\n", any.mas[0]);
		free(any.str);
		exit(EXIT_FAILURE);
	}
	wait(0);
	ft_free_mass(any.mas);
	if (any.str)
		free(any.str);
}

void ft_executor(t_monna *lisa)
{
	int count;

	if (lisa->flag_file)
		count = 1;
	else
		count = 2;
	while (count < ft_lenmassive(lisa->tokens) - 2)
	{
		ft_pipe(lisa, count);
		ft_any_argument(lisa, count);
		ft_pipe_stdin(lisa);
		count++;
	}
	if (lisa->flag_herodoc && ft_lenmassive(lisa->tokens) == 4)
		ft_pipe(lisa, count);
	if (lisa->flag_file)
		lisa->fd = open(lisa->tokens[ft_lenmassive(lisa->tokens) - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		lisa->fd = open(lisa->tokens[ft_lenmassive(lisa->tokens) - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	dup2(lisa->fd, 1);
	ft_any_argument(lisa, count);
	close(lisa->fd);
}

void ft_red_4_sup(t_red_4 *aa, t_monna *lisa, char *count)
{
	while (1)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(1, &aa->str);
		if (!ft_strcmp(aa->str, count))
		{
			if (aa->str)
				free(aa->str);
			break;
		}
		if (!lisa->list)
		{
			lisa->list = ft_lstnew((char *)aa->str);
			aa->tmp = lisa->list;
		}
		else
		{
			aa->tmp->next = ft_lstnew((char *)aa->str);
			aa->tmp = aa->tmp->next;
		}
	}
}

void ft_heredoc(t_monna *lisa)
{
	t_red_4 aa;

	lisa->flag_red_output = 1;
	lisa->flag_red_4 = 1;
	ft_red_4_sup(&aa, lisa, lisa->tokens[1]);
	aa.tmp = lisa->list;
	aa.fd = open("1", O_WRONLY | O_TRUNC | O_CREAT, 0200 | 0400);
	while (aa.tmp)
	{
		if (aa.tmp->content)
			ft_putendl_fd(aa.tmp->content, aa.fd);
		aa.tmp = aa.tmp->next;
	}
	ft_list_clear(&lisa->list);
	lisa->list = NULL;
	close(aa.fd);
	aa.fd = open("1", O_RDONLY);
	dup2(aa.fd, 0);
	close(aa.fd);
	lisa->flag_herodoc = 1;
}
