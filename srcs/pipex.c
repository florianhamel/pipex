/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:02:39 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 01:20:58 by fhamel           ###   ########.fr       */
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

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_free((void **)&arr[i]);
		i++;
	}
	ft_free((void **)arr);
}

char	*concat_path_bin(const char *path, const char *name_bin)
{
	char	*path_bin;
	int		i;
	int		j;

	path_bin = alloc(sizeof(char), \
	ft_strlen(path) + ft_strlen(name_bin) + 2);
	i = 0;
	while (path[i])
	{
		path_bin[i] = path[i];
		i++;
	}
	path_bin[i] = '/';
	i++;
	j = 0;
	while (name_bin[j])
	{
		path_bin[i] = name_bin[j];
		i++;
		j++;
	}
	path_bin[i] = '\0';
	return (path_bin);
}

char	*path_maker(char **arr_paths, const char *name_bin)
{
	char	*path_bin;
	int	i;

	path_bin = NULL;
	i = 0;
	while (arr_paths[i])
	{
		path_bin = concat_path_bin(arr_paths[i], name_bin);
		// printf("path_bin = %s\n", path_bin);
		if (access(path_bin, F_OK) == ACCESS)
			return (path_bin);
		i++;
	}
	return (NULL);
}

void	exit_wrong_cmd(char *name_bin)
{
	ft_putstr_fd(name_bin, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("Command not found\n", 2);
	exit(127);
}

char	*get_path_bin(t_cmd *cmd, char **envp)
{
	char	**arr_cmd;
	char	*name_bin;
	char	**arr_paths;
	char	*path_bin;
	int		i;

	arr_cmd = ft_split(cmd->data, ' ');
	name_bin = ft_strdup(arr_cmd[0]);
	free_split(arr_cmd);
	arr_paths = NULL;
	path_bin = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] && ft_strncmp(envp[i], "PATH", 4) == 0)
	{
		arr_paths = ft_split(&envp[i][5], ':');
		path_bin = path_maker(arr_paths, name_bin);
		free_split(arr_paths);
	}
	if (!path_bin)
		exit_wrong_cmd(name_bin);
	ft_free((void **)&name_bin);
	return (path_bin);
}

int		ft_is_ws(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	str_is_ws(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_ws(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**get_args(t_cmd *cmd, char **envp)
{
	char	*path_bin;
	char	**args;

	if (str_is_ws(cmd->data))
		exit_wrong_cmd((char *)cmd->data);
	path_bin = get_path_bin(cmd, envp);
	args = ft_split(cmd->data, ' ');
	ft_free((void **)&args[0]);
	args[0] = path_bin;
	return (args);
}

int	pipex_first(t_files files, t_cmd *cmd, char **envp)
{
	int			fd[2];
	int			infile;
	char		**args;
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
		args = get_args(cmd, envp);
		dup_std(infile, fd[1]);
		close(infile);
		pipe_closing(fd);
		if (execve(args[0], (char *const *)args, envp) == FAILURE)
			ft_exit(NULL);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}

void	pipex_last(int fd_next, t_files files, t_cmd *cmd, char **envp)
{
	int		outfile;
	char	**args;
	pid_t	pid;

	outfile = -1;
	args = NULL;
	pid = fork();
	if (pid < 0)
		ft_exit(NULL);
	if (pid == CHILD)
	{
		outfile = check_and_open(files.outfile, OUTFILE);
		args = get_args(cmd, envp);
		dup2(fd_next, 0);
		dup2(outfile, 1);
		close(fd_next);
		close(outfile);
		if (execve(args[0], (char *const *)args, envp) == FAILURE)
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
