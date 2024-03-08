/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:00:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 16:18:57 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_filerror(int errnu, t_pipex *pipex, char *filename, int infile)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errnu), 2);
	// ft_printf("pipex: %s:\n",); maybe do not need fpf
	if (infile)
		pipex->fdin_failed = 1;
	else
		pipex->fdout_failed = 1;
}

void	ft_cmd_error(char *cmd, int permission)
{
	ft_putstr_fd("pipex: ", 2);
	if (permission == 1)
	{
		if (cmd[0])
			ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		return ;
	}
	if (permission == 2)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		return ;
	}
	perror(cmd);
	
}

void	ft_exit_error(t_pipex *pipex, int free, int status)
{
	if (free)
	{
		perror("pipex: ");
		ft_free_pipex(pipex);
	}
	exit(status);
}


