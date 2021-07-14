/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:34:44 by fhamel            #+#    #+#             */
/*   Updated: 2021/07/12 17:09:53 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

/*
** multi_pipex_bonus.c
*/
int		pipex_mid(int fd_next, t_cmd *cmd, char **envp);
void	multi_pipex(t_files files, t_cmd *lst_cmd, char **envp);
void	start_multi_pipex(int ac, char **av, char **envp);

/*
** here_doc_bonus.c
*/
void	get_here_doc(const char *lim, int fd_hd);
void	here_doc_last(int fd_next, t_files files, t_cmd *cmd, char **envp);
int		here_doc_first(const char *lim, t_cmd *cmd, char **envp);
void	here_doc_pipex(const char *lim, t_files files, t_cmd *lst_cmd, \
		char **envp);
void	start_here_doc(const char *lim, int ac, char **av, char **envp);

#endif