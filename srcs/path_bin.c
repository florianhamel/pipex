/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 12:16:32 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/23 00:21:30 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

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
		ft_free((void **)&name_bin);
	}
	if (!path_bin)
		free_exit_wrong_cmd(cmd);
	ft_free((void **)&path_bin);
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

char	*get_bin(t_cmd *cmd)
{
	char	**arr_cmd;
	char	*path_bin;
	int		i;

	arr_cmd = ft_split(cmd->data, ' ');
	path_bin = NULL;
	i = 0;
	while (arr_cmd[0][i] && arr_cmd[0][i] != '/')
		i++;
	if (!arr_cmd[0][i])
	{
		ft_free_arr(arr_cmd);
		return (path_bin);
	}
	if (access(arr_cmd[0], F_OK) == FAILURE)
		ft_exit(arr_cmd[0]);
	path_bin = ft_strdup(arr_cmd[0]);
	ft_free_arr(arr_cmd);
	return (path_bin);
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
		ft_free((void **)&name_bin);
	}
	if (!path_bin)
		exit_wrong_cmd(cmd);
	return (path_bin);
}
