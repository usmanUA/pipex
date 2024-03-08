/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:02:38 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 16:06:53 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status)+128);
	return (1);
}

int	ft_failure_status(int file_status, char *cmd)
{
	if (file_status)
		return (1);
	if (!cmd)
		return (127);
	if (!ft_strncmp(cmd, "NO_EXEC", 7) || !ft_strncmp(cmd, "DIR", 3))
		return (126);
	return (0);
}

int	ft_pair_failed(t_pipex *ppx, int cmd_num, int i)
{
	if (cmd_num == -1)
		return (ft_failure_status(ppx->fdin_failed, ppx->cmds[i]));
	else if (cmd_num == 1)
		return (ft_failure_status(ppx->fdout_failed, ppx->cmds[i]));
	else
		return (ft_failure_status(0, ppx->cmds[i]));
	return (0);
}

void	ft_free_pipex(t_pipex *pipex)
{
	int	ind;

	ind = -1;
	if (pipex->cmd_args[0])
	{
		while (pipex->cmd_args[++ind])
			ft_free(pipex->cmd_args[ind], 0);
		free(pipex->cmd_args);
	}
	if (pipex->paths)
		ft_free(pipex->paths, 0);
	if (pipex->cmds)
		ft_free(pipex->cmds, pipex->idx + 1);
	if (pipex->fd_in > -1)
		close(pipex->fd_in);
	if (pipex->fd_out > -1)
		close(pipex->fd_out);
}

void	ft_initialize_pipex(t_pipex *pipex, int tot_cmds)
{
	pipex->fd_in = -2;
	pipex->fdin_failed = 0;
	pipex->fd_out = -2;
	pipex->fdout_failed = 0;
	pipex->idx = -1;
	pipex->start = 2;
	pipex->here_doc = false;
	pipex->paths = NULL;
	pipex->cmds = NULL;
	pipex->cmd_args = NULL;
	pipex->tot_cmds = tot_cmds;
}

void	ft_print_pipex(t_pipex *pipex)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("The commands:\n");
	while (++i < pipex->tot_cmds)
		printf("cmd in PIPEX: %s\n", pipex->cmds[i]);
	i = -1;
	while (++i < pipex->tot_cmds)
	{
		j = -1;
		while (pipex->cmd_args[i][++j])
			printf("cmd_args in PIPEX:%s\n", pipex->cmd_args[i][j]);
	}
	printf("pipe->fdin_failed: %d\n", pipex->fdin_failed);
	printf("pipe->fdout_failed: %d\n", pipex->fdout_failed);
}
