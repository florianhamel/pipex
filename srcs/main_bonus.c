/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:37:01 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/23 00:55:32 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"

int	main(int ac, char **av, char **envp)
{
	const char	*lim;
	char		*usage;

	usage = "usage: ./pipex infile \"cmd1\" ... \"cmdn\" outfile\n\
OR ./pipex here_doc LIMITER \"cmd1\" ... \"cmdn\" outfile\n";
	lim = NULL;
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac > 5)
	{
		lim = av[2];
		start_here_doc(lim, ac, av, envp);
	}
	else if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		write(STDERR_FILENO, usage, ft_strlen(usage));
		return (2);
	}
	else if (ac > 4)
		start_multi_pipex(ac, av, envp);
	else
	{
		write(STDERR_FILENO, usage, ft_strlen(usage));
		return (1);
	}
	return (0);
}
