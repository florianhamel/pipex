/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:39:48 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 21:18:18 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"
#include "libft.h"

int	pipex_mid(int fd_next, t_cmd *cmd, char **envp)
{
	int			fd[2];
	char *const	*args;
	pid_t		pid;

	if (pipe(fd) == FAILURE)
		ft_exit(NULL);
	args = NULL;
	pid = fork();
	if (pid < 0)
		ft_exit(NULL);
	else if (pid == CHILD)
	{
		args = get_args(cmd, envp);
		dup_stdio(fd_next, fd[1]);
		close(fd_next);
		pipe_closing(fd);
		if (execve(args[0], args, envp) == FAILURE)
			ft_exit(NULL);
	}
	close(fd_next);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}

void	multi_pipex(t_files files, t_cmd *lst_cmd, char **envp)
{
	int		fd_next;	
	t_cmd	*current;

	fd_next = -1;
	current = lst_cmd;
	while (current != NULL)
	{
		if (current->prev == NULL)
			fd_next = pipex_first(files, current, envp);
		else if (current->next == NULL)
			pipex_last(fd_next, files, current, envp);
		else
			fd_next = pipex_mid(fd_next, current, envp);
		current = current->next;
	}
}

void	start_multi_pipex(int ac, char **av, char **envp)
{
	t_cmd	*lst_cmd;
	t_files	files;
	t_cmd	*next;

	files.infile = av[1];
	files.outfile = av[ac - 1];
	lst_cmd = get_lst_cmd(ac, av);
	multi_pipex(files, lst_cmd, envp);
	while (lst_cmd)
	{
		next = lst_cmd->next;
		ft_free((void **)&lst_cmd);
		lst_cmd = next;
	}
}
