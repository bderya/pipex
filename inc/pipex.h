/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:13:57 by bderya            #+#    #+#             */
/*   Updated: 2022/09/18 23:37:39 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	pid_t	id;
	char	*cfile[2];
	int		fd[2];
	char	**cmd1;
	char	**cmd2;
}			t_data;

char	*pathwriter(char *cmd, char **envp);
void	create_pipe(char **envp, t_data *pipex);
void	error(void);

#endif