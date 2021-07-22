/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:21:17 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/22 17:00:50 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	*alloc(size_t size, size_t len)
{
	void	*alloc;

	alloc = malloc(size * len);
	if (!alloc)
		ft_exit(NULL);
	return (alloc);
}

int	str_is_ws(const char *str)
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

void	create_outfile(char *file_name, int mode)
{
	int	fd;

	fd = -1;
	if (mode == OUTFILE)
	{
		fd = open(file_name, O_CREAT | O_TRUNC, 0666);
		if (fd != FAILURE)
			close(fd);
	}
	else
	{
		fd = open(file_name, O_CREAT | O_APPEND, 0666);
		if (fd != FAILURE)
			close(fd);
	}
}

void	ft_execve(char **args, char **envp)
{
	if (execve(args[0], (char *const *)args, envp) == FAILURE)
		ft_exit(NULL);
}

void	init_first(int *infile, char ***args)
{
	*infile = -1;
	*args = NULL;
}
