/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:13:57 by bderya            #+#    #+#             */
/*   Updated: 2022/09/18 19:41:30 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
	Declaring general way how to do it,
	General all variable declaring that area
	Split the arguments
*/
void	dec(char **argv, t_data *pipex)
{
	pipex->cfile[0] = argv[1];
	pipex->cfile[1] = argv[4];
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
}

/*
	Main, getting 3 different object 
	Arg counter = calculating how many argumant entered.
	Arg variable = char variale.
	Enviorenment pointer = we can use/control to environment
	If counter is not equal 4( + program name), finish program otherwise continuing.
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;

	if (argc == 5)
	{
		dec(argv, &pipex);
		create_pipe(envp, &pipex);
	}
	else
		error();
	return (0);
}
