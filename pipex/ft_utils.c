#include "pipex.h"

int	ft_lenmassive(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_free_mass(char **mas)
{
	int	i;

	i = 0;
	while (mas[i])
		free(mas[i++]);
	free(mas);
}

void	ft_pipe_stdin(t_monna *lisa)
{
	dup2(lisa->fd_output, 1);
	dup2(lisa->fildes[0], 0);
	close(lisa->fildes[0]);
}

void	ft_pipe(t_monna *l, int i)
{
	pipe(l->fildes);
	dup2(l->fildes[1], 1);
	close(l->fildes[1]);
}

void	ft_list_clear(t_list **head)
{
	t_list	*tmp;
	t_list	*list;

	list = *head;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list->content);
		free(list);
		list = tmp;
	}
}
