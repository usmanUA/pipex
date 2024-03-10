/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:05:21 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 17:23:40 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_validate_files(char *infile, char *outfile, t_pipex *ppx)
{
	ppx->fd_in = open(infile, O_RDONLY);
	if (ppx->fd_in == -1)
		ft_filerror(errno, ppx, infile, 1);
	if (ppx->here_doc)
	{
		// write(1, "here\n", 5);
		ppx->fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	else
	{
		// write(1, "here\n", 5);
		ppx->fd_out = open(outfile, O_WRONLY | O_CREAT| O_TRUNC, 0666);
	}
	if (ppx->fd_out == -1)
		ft_filerror(errno, ppx, outfile, 1);
}

static void	ft_malloc_struct(t_pipex *pipex, char ***cmds, char ****cmd_args, int idx)
{
	if (idx)
	{
		pipex->cmd_args[pipex->idx] = (char **)malloc(2 *  sizeof(char *));
		if (!pipex->cmd_args[pipex->idx])
			ft_exit_error(pipex, 1, EXIT_FAILURE);
		return ;
	}
	*cmds = (char **)malloc((pipex->tot_cmds + 1) * sizeof(char *));
	if (!(*cmds))
		ft_exit_error(pipex, 1, EXIT_FAILURE);
	*cmd_args = (char ***)malloc((pipex->tot_cmds + 1) * sizeof(char **));
	if (!(*cmd_args))
		ft_exit_error(pipex, 1, EXIT_FAILURE);
}

void	ft_handle_absolute(t_pipex *ppx)
{
	int fd;

	fd = -2;
	if (!access(ppx->cmd_args[ppx->idx][0], F_OK))
	{
		fd = open(ppx->cmd_args[ppx->idx][0], __O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			ft_cmd_error(ppx->cmd_args[ppx->idx][0], 2);
			ppx->cmds[ppx->idx] = ft_strdup("DIR");
		}
		else if (access(ppx->cmd_args[ppx->idx][0], X_OK) == -1)
		{
			ft_cmd_error(ppx->cmd_args[ppx->idx][0], 0);
			ppx->cmds[ppx->idx] = ft_strdup("NO_EXEC");
		}
		else
			ppx->cmds[ppx->idx] = ft_strdup(ppx->cmd_args[ppx->idx][0]);	
	}
	else
	{
		ppx->cmds[ppx->idx] = NULL;
		ft_cmd_error(ppx->cmd_args[ppx->idx][0], 1);
	}
}

int	ft_nullstr_spaces(t_pipex *ppx, char **args)
{
	int i;

	i = -1;
	if (args[ppx->idx+ppx->start][0] == '\0')
	{
		ft_cmd_error("", 1);
		ppx->cmds[ppx->idx] = NULL;
		ppx->cmd_args[ppx->idx] = NULL;
		return (1) ;
	}
	else
	{
		while (args[ppx->idx + ppx->start][++i])
		{
			if (!ft_isspace(args[ppx->idx + ppx->start][i]))
				return (0);
		}
		ft_cmd_error(args[ppx->idx+ppx->start], 1);
		ppx->cmds[ppx->idx] = ft_strdup(args[ppx->idx+ppx->start]);
		ft_malloc_struct(ppx, NULL, NULL, 1);
		ppx->cmd_args[ppx->idx][0] = ft_strdup(args[ppx->idx+ppx->start]);
		ppx->cmd_args[ppx->idx][1] = NULL;
		return (1);
	}
	return (0);
}

void	ft_save_commands(char **args, char **envp, t_pipex *ppx)
{
	ft_malloc_struct(ppx, &ppx->cmds, &ppx->cmd_args, 0);
	ppx->paths = ft_split(ft_give_path(envp), NULL, ':', 0);
	while (++ppx->idx < ppx->tot_cmds)
	{
		if (ft_nullstr_spaces(ppx, args))
			continue ;
		ppx->cmd_args[ppx->idx] = ft_split(args[ppx->idx + ppx->start], "\'\"", ' ', 1);
		if (ft_ispresent(ppx->cmd_args[ppx->idx][0], '/'))
			ft_handle_absolute(ppx);
		else
			ft_valid_command(ppx);
	}
	ppx->cmds[ppx->idx] = NULL;
	ppx->cmd_args[ppx->idx] = NULL;
}

void	ft_valid_command(t_pipex *ppx)
{
	char	*cmd_path;
	int		i;

	i = -1;
	cmd_path = NULL;
	while (ppx->paths[++i])
	{
		cmd_path = ft_join_path(ppx->paths[i], ppx);
		if (!access(cmd_path, F_OK))
		{
			if (access(cmd_path, X_OK) == -1)
			{
				ft_cmd_error(ppx->cmd_args[ppx->idx][0], 0);
				ppx->cmds[ppx->idx] = ft_strdup("NO_EXEC");
			}
			else
				ppx->cmds[ppx->idx] = cmd_path;
			return ;
		}
		free(cmd_path);
	}
	ppx->cmds[ppx->idx] = NULL;
	ppx->cmd_args[ppx->idx + 1] = NULL; // WHY? idx = 0, but idx = 1 is file, why corrupt idx = 1?
	ft_cmd_error(ppx->cmd_args[ppx->idx][0], 1);
}

char	*ft_join_path(char *path, t_pipex *ppx)
{
	char	*path_to_cmd;
	char	*cmd_path;

	path_to_cmd = ft_strjoin(path, "/");
	if (!path_to_cmd)
		ft_exit_error(ppx, 1, EXIT_FAILURE);
	cmd_path = ft_strjoin(path_to_cmd, ppx->cmd_args[ppx->idx][0]);
	if (!cmd_path)
	{
		free(path_to_cmd);
		ft_exit_error(ppx, 1, EXIT_FAILURE);
	}
	if (path_to_cmd)
		free(path_to_cmd);
	return (cmd_path);
}
