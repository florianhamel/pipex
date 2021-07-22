/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 22:46:15 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/22 19:25:30 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	main(int ac, char **av, char **envp)
{
	char	*usage;

	usage = "usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n";
	if (ac == 5)
		start_pipex(ac, av, envp);
	else
		write(STDERR_FILENO, usage, ft_strlen(usage));
	return (0);
}
