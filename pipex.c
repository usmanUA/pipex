/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:48:54 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/22 13:02:52 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_pipex(t_pipex *pipex)
{
  if (pipex->cmds)
    ft_free(pipex->cmds);
  if (pipex->cmd_args)
    {
      while (*pipex->cmd_args)
	{
	  ft_free(*pipex->cmd_args);
	  pipex->cmd_args++;
	}
    }
}

void	ft_initialize_pipex(t_pipex *pipex, int tot_cmds)
{
  pipex->here_doc = false;
  pipex->bonus = false;
  pipex->fd_in = 0;
  pipex->fd_out = 0;
  pipex->cmds = 0;
  pipex->cmd_args = 0;
  pipex->tot_cmds = tot_cmds;
}

int main(int argc, char *argv[], char **envp)
{
    t_pipex pipex;
    
    if (argc > 1)
    {
      	ft_initialize_pipex(&pipex, argc - 3);
	      ft_validate_files(argc-1, argv, &pipex);
        ft_save_commands(argv, envp, &pipex);
        write(1, "validated\n", 10);
        ft_save_args(argv, &pipex);
        ft_execute(&pipex);
        ft_free_pipex(&pipex);
    }
    return (0);
}
