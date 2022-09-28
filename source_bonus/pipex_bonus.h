#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct pipex_bonus
{
	int		flag;
	int		fd[2];
	pid_t	id;
	char	**cmd;
	int		file;
}			t_pipex;



#endif