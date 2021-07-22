/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:47:26 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/23 00:34:23 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "gnl_bonus.h"
#include "libft.h"

void	get_here_doc(const char *lim, int fd_hd)
{
	char	*line;

	line = NULL;
	while (ft_strncmp(line, lim, ft_strlen(lim) + 1))
	{
		ft_putstr_fd(line, fd_hd);
		ft_putstr_fd("\n", fd_hd);
		ft_free((void **)&line);
		write(0, "> ", 2);
		if (get_next_line(0, &line) == FAILURE)
			ft_exit(NULL);
	}
	ft_free((void **)&line);
}

void	here_doc_last(int fd_next, t_files files, t_cmd *cmd, char **envp)
{
	int			outfile;
	char *const	*args;
	pid_t		pid;
	int			status;

	outfile = -1;
	args = NULL;
	pid = fork();
	if (pid < 0)
		ft_exit(NULL);
	if (pid == CHILD)
	{
		outfile = check_and_open(files.outfile, OUTFILE_APPEND, cmd);
		args = get_args(cmd, envp);
		dup2(fd_next, 0);
		dup2(outfile, 1);
		close(fd_next);
		close(outfile);
		if (execve(args[0], args, envp) == FAILURE)
			ft_exit(NULL);
	}
	close(fd_next);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
		free_exit(cmd, WEXITSTATUS(status));
}

int	here_doc_first(const char *lim, t_files files, t_cmd *cmd, char **envp)
{
	int			fd_hd[2];
	int			fd[2];
	char		**args;
	pid_t		pid;

	if (pipe(fd_hd) == FAILURE || pipe(fd) == FAILURE)
		ft_exit(NULL);
	args = NULL;
	pid = fork();
	if (pid < 0)
		ft_exit(NULL);
	else if (pid == CHILD)
	{
		get_here_doc(lim, fd_hd[1]);
		create_outfile(files.outfile, OUTFILE_APPEND);
		args = get_args(cmd, envp);
		dup_stdio(fd_hd[0], fd[1]);
		pipe_closing(fd_hd);
		ft_execve(args, envp);
	}
	close (fd[1]);
	pipe_closing(fd_hd);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}

void	here_doc_pipex(const char *lim, t_files files, t_cmd *lst_cmd, \
char **envp)
{
	int		fd_next;	
	t_cmd	*current;

	fd_next = -1;
	current = lst_cmd;
	while (current != NULL)
	{
		if (current->prev == NULL)
			fd_next = here_doc_first(lim, files, current, envp);
		else if (current->next == NULL)
			here_doc_last(fd_next, files, current, envp);
		else
			fd_next = pipex_mid(fd_next, current, envp);
		current = current->next;
	}
}

void	start_here_doc(const char *lim, int ac, char **av, char **envp)
{
	t_cmd	*lst_cmd;
	t_files	files;
	t_cmd	*next;

	files.infile = 0;
	files.outfile = av[ac - 1];
	lst_cmd = get_lst_cmd(ac, av);
	here_doc_pipex(lim, files, lst_cmd, envp);
	while (lst_cmd)
	{
		next = lst_cmd->next;
		ft_free((void **)&lst_cmd);
		lst_cmd = next;
	}
}
