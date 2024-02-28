/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:02:52 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/28 13:24:05 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_pipex(t_pipex *pipex)
{
	int	ind;

	ind = -1;
	if (pipex->paths)
		ft_free(pipex->paths);
	if (pipex->cmds)
		ft_free(pipex->cmds);
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[++ind])
			ft_free(pipex->cmd_args[ind]);
		free(pipex->cmd_args);
	}
	ind = -1;
	if (pipex->temp_cmds)
	{
		while (pipex->temp_cmds[++ind])
			ft_free(pipex->temp_cmds[ind]);
		free(pipex->temp_cmds);
	}	
}

void	ft_initialize_pipex(t_pipex *pipex, int tot_cmds)
{
	pipex->here_doc = false;
	pipex->bonus = false;
	pipex->fd_in = 0;
	pipex->fd_out = 0;
	pipex->paths = NULL;
	pipex->temp_cmds = NULL;
	pipex->cmds = NULL;
	pipex->cmd_args = NULL;
	pipex->tot_cmds = tot_cmds;
}

void	ft_print_pipex(t_pipex *pipex)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (pipex->cmds[++i])
		printf("cmd in PIPEX: %s\n", pipex->cmds[i]);
	// i = -1;
	// while (pipex->cmd_args[++i])
	// {
	// 	j = -1;
	// 	while (pipex->cmd_args[i][++j])
	// 		printf("cmd_args in PIPEX: %s\n", pipex->cmd_args[i][j]);
	// }
		
}

void	ft_print_args(int argc, char **args)
{
	int i;
	i = 1;
	while (++i < argc -1)
		printf("args: %s\n", args[i])	;
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	pipex;
	char	**cm;
	char	***cmds;

	cm = NULL;
	cmds = NULL;
	// ft_print_args(argc, argv);
	if (argc > 1)
	{
		ft_initialize_pipex(&pipex, argc - 3);
		ft_validate_files(argc - 1, argv, &pipex);
		ft_save_commands(argv, envp, &pipex);
		ft_save_args(argv, &pipex);
		// ft_print_pipex(&pipex);
		ft_execute(&pipex);
		ft_free_pipex(&pipex);
	}
	return (0);
}
