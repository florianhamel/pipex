/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:37:01 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/17 18:14:52 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"

int	main(int ac, char **av, char **envp)
{
	const char	*lim;

	lim = NULL;
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac > 5)
	{
		lim = av[2];
		start_here_doc(lim, ac, av, envp);
	}
	else if (ft_strncmp(av[1], "here_doc", 8) == 0)
		write(1, "Wrong number of arguments for here_doc.\n", 40);
	else if (ac > 4)
		start_multi_pipex(ac, av, envp);
	else
		write(1, "Wrong number of arguments.\n", 27);
	return (0);
}
