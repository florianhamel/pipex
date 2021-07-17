/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 18:37:14 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 18:39:16 by fhamel           ###   ########.fr       */
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
	ft_putstr_fd((char *)cmd->data, STDERR_FILENO);
	ft_free_lst(cmd);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Command not found\n", STDERR_FILENO);
	exit(127);
}

void	free_exit_wrong_cmd(t_cmd *cmd)
{
	ft_free_lst(cmd);
	exit(127);
}