/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:02:39 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/12 17:19:06 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	check_and_open(const char *file, int mode)
{
	int	fd;

	if (mode == OUTFILE_APPEND)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if (mode == INFILE)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == FAILURE)
		ft_exit(file);
	return (fd);
}

char *const	*get_args(t_cmd *cmd)
{
	const char	**args;

	args = alloc(sizeof(char *), 4);
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd->data;
	args[3] = NULL;
	return ((char *const *)args);
}

int	pipex_first(t_files files, t_cmd *cmd, char **envp)
{
	int			fd[2];
	int			infile;
	char *const	*args;
	pid_t		pid;

	if (pipe(fd) == FAILURE)
		ft_exit(NULL);
	infile = -1;
	args = NULL;
	pid = fork();
	if (pid < 0)
		ft_exit(NULL);
	else if (pid == CHILD)
	{
		infile = check_and_open(files.infile, INFILE);
		args = get_args(cmd);
		dup_std(infile, fd[1]);
		close(infile);
		pipe_closing(fd);
		if (execve(args[0], args, envp) == FAILURE)
			ft_exit(NULL);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}

void	pipex_last(int fd_next, t_files files, t_cmd *cmd, char **envp)
{
	int			outfile;
	char *const	*args;
	pid_t		pid;

	outfile = -1;
	args = NULL;
	pid = fork();
	if (pid < 0)
		ft_exit(NULL);
	if (pid == CHILD)
	{
		outfile = check_and_open(files.outfile, OUTFILE);
		args = get_args(cmd);
		dup2(fd_next, 0);
		dup2(outfile, 1);
		close(fd_next);
		close(outfile);
		if (execve(args[0], args, envp) == FAILURE)
			ft_exit(NULL);
	}
	close(fd_next);
	waitpid(pid, NULL, 0);
}

void	pipex(t_files files, t_cmd *lst_cmd, char **envp)
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
		current = current->next;
	}
}