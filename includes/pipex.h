/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 22:46:38 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/12 16:53:31 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define ACCESS 0
# define FAILURE -1

# define CHILD 0

# define INFILE 0
# define OUTFILE 1
# define OUTFILE_APPEND 2

typedef struct s_files
{
	char	*infile;
	char	*outfile;
}	t_files;

typedef struct s_cmd
{
	const char		*data;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

/*
** start_pipex.c
*/
void		dup_std(int fd1, int fd2);
void		pipe_closing(int fd[2]);
t_cmd		*new_cmd(const char *str, t_cmd *prev);
t_cmd		*get_lst_cmd(int ac, char **av);
void		start_pipex(int ac, char **av, char **envp);

/*
** pipex.c
*/
char *const	*get_args(t_cmd *cmd);
int			check_and_open(const char *file, int mode);
int			pipex_first(t_files files, t_cmd *cmd, char **envp);
void		pipex_last(int fd_next, t_files files, t_cmd *cmd, char **envp);
void		pipex(t_files files, t_cmd *lst_cmd, char **envp);

/*
** utils.c
*/
int			ft_strcmp(const char *s1, const char *s2);
void		ft_free(void **ptr);
void		ft_exit(const char *str_error);
void		*alloc(size_t size, size_t len);

#endif