/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:32:08 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 13:14:43 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_execute(t_pipex *pipex, char **envp)
{
	int		fds[2];
	int		pips;
	int status;
	int pid;

	status = 0;
	pips = pipe(fds);
	if (pips == -1)
		ft_exit_error(pipex, 1, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		ft_exit_error(pipex, 1, EXIT_FAILURE);
	if (pid == 0)
		ft_first_child(pipex, fds, envp);
	else
	{
		close(fds[1]);
		ft_second_child(pipex, fds, &status, envp);
	}
	if (status != 127 && status != 126)
		status = ft_status(status);
	ft_free_pipex(pipex);
	return (status);
}

void	ft_first_child(t_pipex *pipex, int *fds, char **envp)
{
	close(fds[0]);
	if (!ft_pair_failed(pipex, -1, 0))
	{
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		execve(pipex->cmds[0], pipex->cmd_args[0], envp);
		ft_exit_error(pipex, 0, EXIT_FAILURE);
	}
	else
		close(fds[1]);
}

void	ft_second_child(t_pipex *pipex, int *fds, int *status, char **envp)
{
	pid_t	pid;

	pid = 0;
	if (!ft_pair_failed(pipex, 1, 1))
	{
		pid = fork();
		if (pid == -1)
			ft_exit_error(pipex, 1, EXIT_FAILURE);
		if (pid == 0)
		{
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			dup2(pipex->fd_out, STDOUT_FILENO);
			close(pipex->fd_out);
			execve(pipex->cmds[1], pipex->cmd_args[1], envp);
			ft_exit_error(pipex, 0, EXIT_FAILURE);
		}
		else
			waitpid(pid, status, 0);
	}
	else
	{
		close(fds[0]);
		*status = ft_pair_failed(pipex, 1, 1);
	}
}
