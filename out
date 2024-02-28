/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:00:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/22 12:55:39 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_filerror(char *filename)
{
    printf("zsh: no such file or directory: %s\n", filename);
    exit(EXIT_FAILURE);
}

void	ft_cmderror(char *cmd)
{
  printf("-bash: %s: command not found\n", cmd);
}

void	ft_malloc_error(t_pipex *pipex)
{
  perror("malloc");
  ft_free_pipex(pipex);
  exit(EXIT_FAILURE);
}

void    ft_exit_error(char *error_cause, t_pipex *pipex)
{
  perror(error_cause);
  ft_free_pipex(pipex);
  exit(EXIT_FAILURE);
}
