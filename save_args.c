/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:05:06 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/27 13:08:22 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	ft_save_args(char **args, t_pipex *pipex)
{
  int i;

  i = -1;
  pipex->cmd_args = (char ***)malloc((pipex->tot_cmds + 1) * sizeof(char **));
  if (!pipex->cmd_args)
    ft_malloc_error(pipex);
  while (++i < pipex->tot_cmds)
    pipex->cmd_args[i] = ft_split(args[i+2], ' ');
  pipex->cmd_args[i] = NULL;
}
