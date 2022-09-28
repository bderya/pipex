#include "pipex_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void error()
{
	exit(1);
}

void controller(int argc, char **argv, t_pipex *pipex)
{

	if (argc < 5)
		error();
	else
	{
		if (!strncmp(argv[1], "here_doc", 8))
			pipex->flag = 1;
		else
			pipex->flag = 0;
	}
}

char here_doc(char *str)
{
	int ifile;

	ifile = open(".tmp", O_RDONLY | O_WRONLY | O_TRUNC);
	dup2(str, 0);
	dup2(ifile,0);
	close(ifile);
}

static void	calling(char **argv, t_pipex *pipex)
{
	pipex->flag = here_doc(argv[2]);
	pipex->file = open(".tmp", O_RDONLY);
	dup2(pipex->file, 0);
	close(pipex->file);
	unlink(".tmp");
}

static void	calling2(char **argv, t_pipex *pipex)
{
	pipex->file = open(argv[1], O_RDONLY);
	
}

void	last_controller(t_pipex *pipex)
{
	if(pipex->file < 0)
	{
		pipex->flag = -1;
		error();
	}
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	controller(argc, argv, &pipex);
	if (pipex.flag = 1)
	{
		calling(argv, &pipex);
	}
	else
		calling2(argv, &pipex);
	last_controller(&pipex);
	return (0);
	
}