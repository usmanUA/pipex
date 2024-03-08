/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:02:52 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 17:08:28 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
		ft_initialize_pipex(&pipex, argc - 3);
		ft_save_commands(argv, envp, &pipex);
		ft_validate_files(argv[1], argv[argc - 1], &pipex);
		return (ft_execute(&pipex, envp));
	}
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
