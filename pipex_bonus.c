/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:02:52 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 17:27:25 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_print_args(int argc, char **args)
{
	int	i;

	i = 1;
	while (++i < argc - 1)
		printf("args: %s\n", args[i]);
}

void	ft_handle_input_output(int argc, char **argv, t_pipex *pipex)
{
	char	*line;

	// line = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		pipex->start = 3;
		pipex->tot_cmds = argc - 4;
		pipex->here_doc = true;
		pipex->fd_in = open(".infile.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (pipex->fd_in == -1)
			ft_filerror(errno, pipex, ".infile.txt", 1);
		line = get_next_line(0);
		write(1, "here\n", 5);
		while (ft_strncmp(line, argv[2], ft_strlen(argv[2])))
		{
			write(pipex->fd_in, line, ft_strlen(line));
			line = get_next_line(0);
		}
		close(pipex->fd_in);
		ft_validate_files(".infile.txt", argv[argc - 1], pipex);
		return ;
	}
	ft_validate_files(argv[1], argv[argc - 1], pipex);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	pipex;

	if (argc > 4)
	{
		ft_initialize_pipex(&pipex, argc - 3);
		ft_handle_input_output(argc, argv, &pipex);
		ft_save_commands(argv, envp, &pipex);
		ft_print_pipex(&pipex);
		return (ft_execute_bonus(&pipex, envp));
	}
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("Usage: ./pipex <infile> <cmd1> <cmd2> ... <outfile>\n", 1);
	return (0);
}
