/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:13:57 by bderya            #+#    #+#             */
/*   Updated: 2022/09/19 02:13:20 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
	Function finding path to execute
	Finds and returns all paths of the env var. 'PATH', separated by
 	the delimiter ':';
 	Iterate through all available env vars and compare the first 4 charachter
*/
char	*pathwriter(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	*slash;
	char	**paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slash, cmd);
		free(slash);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/*
	That area execute commands,
	Executer the command with execve().
*/
void	run(char **cmd, char **envp)
{
	char	*path;
	int		i;

	i = -1;
	path = pathwriter(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
		{
			free(cmd[i]);
		}
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
	{
		error();
	}
}

/*
	O_WRONLY =  open for writing only 
	O_CREAT  =  create if nonexistant 
	O_TRUNC  =  truncate to zero length
	STDIN_FILENO  = standard input file descriptor
	STDOUT_FILENO = standard output file descriptor
*/
void	processarea2(char *read, char **cmd, char **envp, int *fd)
{
	int	file2;

	file2 = open(read, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (file2 == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	run(cmd, envp);
}

/*
	O_RDONLY	  = open for reading only
	STDIN_FILENO  = standard input file descriptor
	STDOUT_FILENO = standard output file descriptor
	The child created by the fork is the place where the operation takes place
*/
void	processarea1(char *read, char **cmd, char **envp, int *fd)
{
	int	file;

	file = open(read, O_RDONLY);
	if (file == -1)
	{
		error();
	}
	dup2(file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	run(cmd, envp);
}

/*
	That places creating pipe area
	FORK    = System call creates a new process.
	IF ID 	= Negatif value is min child process was unsuccesfull.
	IF ID	= Zero is returned to the newly created child process.
	Waitpid = Wait for a specific child process to end
	That place 
*/
void	create_pipe(char **envp, t_data *pipex)
{
	if (pipe(pipex->fd) == -1)
		error();
	pipex->id = fork();
	if (pipex->id == -1)
		error();
	if (pipex->id == 0)
		processarea1(pipex->cfile[0], pipex->cmd1, envp, pipex->fd);
	waitpid(pipex->id, NULL, 0);
	processarea2(pipex->cfile[1], pipex->cmd2, envp, pipex->fd);
}
