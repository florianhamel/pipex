/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 18:37:14 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/23 00:37:28 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_free_lst(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		next = cmd->next;
		ft_free((void **)&cmd);
		cmd = next;
	}
}

void	ft_exit(const char *str_error)
{
	int	errno;

	perror(str_error);
	exit(errno);
}

void	exit_wrong_cmd(t_cmd *cmd)
{
	char	**arr_cmd;

	arr_cmd = ft_split(cmd->data, ' ');
	ft_putstr_fd(arr_cmd[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Command not found\n", STDERR_FILENO);
	ft_free_arr(arr_cmd);
	free_exit(cmd, 127);
}

void	free_exit(t_cmd *cmd, int error)
{
	ft_free_lst(cmd);
	exit(error);
}
