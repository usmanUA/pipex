/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:32:08 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/01 14:53:35 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execute_bonus(t_pipex *pipex)
{
    int i;

	i = -1;
	dup2(pipex->fd_in, STDIN_FILENO);
	while (++i < pipex->tot_cmds - 1)
		ft_processes(pipex, i);
	dup2(pipex->fd_out, STDOUT_FILENO);
	execve(pipex->cmds[pipex->tot_cmds-1], pipex->cmd_args[pipex->tot_cmds-1], NULL);
}

void	ft_processes(t_pipex *pipex, int ind)
{
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		ft_exit_error("pipe", pipex);
	pid = fork();
	if (pid == -1)
		ft_exit_error("fork", pipex);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(pipex->cmds[ind], pipex->cmd_args[ind], NULL);
		ft_exit_error("execve", pipex);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
	}
}

