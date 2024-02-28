/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:02:52 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/27 13:57:59 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_pipex(t_pipex *pipex)
{
  int ind;

  ind = -1;
  if (pipex->temp_cmds)
    ft_free(pipex->temp_cmds);
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

int main(int argc, char *argv[], char **envp)
{
    t_pipex pipex;
    char **cm;
    char ***cmds;
    
    cm = NULL;
    cmds = NULL;
    if (argc > 1)
    {
      	ft_initialize_pipex(&pipex, argc - 3);
	ft_validate_files(argc - 1, argv, &pipex);
        ft_save_commands(argv, envp, &pipex);
        ft_save_args(argv, &pipex);
        ft_execute(&pipex);
        ft_free_pipex(&pipex);
    }
    return (0);
}
