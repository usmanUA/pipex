/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:00:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/01 16:38:29 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_filerror(char *filename)
{
	printf("pipex: no such file or directory: %s\n", filename);
	exit(EXIT_FAILURE);
}

void	ft_cmd_error_exit(char *cmd, t_pipex *pipex)
{
	printf("pipex:  command not found: %s\n", cmd);
	ft_free_pipex(pipex);
	exit(EXIT_FAILURE);
}

void	ft_exit_error(char *error_cause, t_pipex *pipex)
{
	perror(error_cause);
	ft_free_pipex(pipex);
	exit(EXIT_FAILURE);
}
