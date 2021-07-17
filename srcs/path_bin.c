/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 12:16:32 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 13:43:06 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	exit_wrong_cmd(char *name_bin)
{
	ft_putstr_fd(name_bin, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Command not found\n", STDERR_FILENO);
	exit(127);
}

void	check_cmd_found(t_cmd *cmd, char **envp)
{
	char	**arr_cmd;
	char	*name_bin;
	char	**arr_paths;
	char	*path_bin;
	int		i;

	arr_cmd = ft_split(cmd->data, ' ');
	name_bin = ft_strdup(arr_cmd[0]);
	ft_free_arr(arr_cmd);
	arr_paths = NULL;
	path_bin = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] && ft_strncmp(envp[i], "PATH", 4) == 0)
	{
		arr_paths = ft_split(&envp[i][5], ':');
		path_bin = path_maker(arr_paths, name_bin);
		ft_free_arr(arr_paths);
	}
	if (!path_bin)
		exit(127);
	ft_free((void **)&name_bin);
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
	int		i;

	path_bin = NULL;
	i = 0;
	while (arr_paths[i])
	{
		path_bin = concat_path_bin(arr_paths[i], name_bin);
		if (access(path_bin, F_OK) == ACCESS)
			return (path_bin);
		ft_free((void **)&path_bin);
		i++;
	}
	return (NULL);
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
	ft_free_arr(arr_cmd);
	arr_paths = NULL;
	path_bin = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] && ft_strncmp(envp[i], "PATH", 4) == 0)
	{
		arr_paths = ft_split(&envp[i][5], ':');
		path_bin = path_maker(arr_paths, name_bin);
		ft_free_arr(arr_paths);
	}
	if (!path_bin)
		exit_wrong_cmd(name_bin);
	ft_free((void **)&name_bin);
	return (path_bin);
}