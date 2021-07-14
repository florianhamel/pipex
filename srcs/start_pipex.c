/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:45:38 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/12 17:01:28 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_std(int fd1, int fd2)
{
	if (dup2(fd1, 0) == FAILURE)
		ft_exit(NULL);
	if (dup2(fd2, 1) == FAILURE)
		ft_exit(NULL);
}

void	pipe_closing(int fd[2])
{
	if (close(fd[0]) == FAILURE)
		ft_exit(NULL);
	if (close(fd[1]) == FAILURE)
		ft_exit(NULL);
}

t_cmd	*new_cmd(const char *str, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = alloc(sizeof(t_cmd), 1);
	cmd->data = str;
	cmd->prev = prev;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*get_lst_cmd(int ac, char **av)
{
	t_cmd	*lst_cmd;
	t_cmd	*cmd;
	t_cmd	*prev;
	int		i;

	prev = NULL;
	if (ft_strcmp(av[1], "here_doc") == 0)
		i = 3;
	else
		i = 2;
	while (i < ac - 1)
	{
		cmd = new_cmd(av[i], prev);
		if (prev)
			prev->next = cmd;
		else
			lst_cmd = cmd;
		prev = cmd;
		i++;
	}
	return (lst_cmd);
}

void	start_pipex(int ac, char **av, char **envp)
{
	t_cmd	*lst_cmd;
	t_files	files;

	files.infile = av[1];
	files.outfile = av[ac - 1];
	lst_cmd = get_lst_cmd(ac, av);
	pipex(files, lst_cmd, envp);
}
