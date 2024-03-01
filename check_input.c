/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:05:21 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/01 17:05:06 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_validate_files(int argc, char **args, t_pipex *pipex)
{
	pipex->fd_in = open(args[1], O_RDONLY);
	if (pipex->fd_in == -1)
		ft_filerror(args[1]);
	pipex->fd_out = open(args[argc], O_WRONLY | O_CREAT, 0644);
	if (pipex->fd_out == -1)
		ft_filerror(args[argc]);
}

char	*ft_give_path(char **envp)
{
	char	*path;

	path = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			path = *envp;
			break ;
		}
		envp++;
	}
	return (&path[5]);
}

void	ft_malloc_struct(t_pipex *pipex, char ***cmds, char ****cmd_args)
{
	*cmds = (char **)malloc((pipex->tot_cmds + 1) * sizeof(char *));
	if (!(*cmds))
		ft_exit_error("malloc", pipex);
	*cmd_args = (char ***)malloc((pipex->tot_cmds + 1) * sizeof(char **));
	if (!(*cmd_args))
		ft_exit_error("malloc", pipex);
}

void	ft_save_commands(char **args, char **envp, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->idx = 1;
	ft_malloc_struct(pipex, &pipex->cmds, &pipex->cmd_args);
	pipex->paths = ft_split(ft_give_path(envp), ':');
	while (++pipex->idx < pipex->tot_cmds)
	{
		pipex->cmd_args[pipex->idx] = ft_split(args[pipex->idx + 2], ' ');
		if (ft_absolute_path(pipex->cmd_args[pipex->idx][0]))
		{
			if (!access(pipex->cmd_args[pipex->idx][0], F_OK | X_OK))
				pipex->cmds[pipex->idx] = ft_strdup(pipex->cmd_args[pipex->idx][0]);
			else
			{
				pipex->cmds[pipex->idx] = NULL;
				ft_cmd_error_exit(pipex->cmd_args[pipex->idx][0], pipex);
			}
		}
		else
			ft_valid_command(pipex, pipex->idx);
	}
	pipex->cmds[pipex->idx] = NULL;
	pipex->cmd_args[pipex->idx] = NULL;	
}

void	ft_valid_command(t_pipex *pipex, int index)
{
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	while (pipex->paths[i])
	{
		cmd_path = ft_join_path(pipex->paths[i], pipex, index);
		i++;
		if (!access(cmd_path, F_OK | X_OK))
		{
			pipex->cmds[index] = cmd_path;
			return ;
		}
		free(cmd_path);
	}
	pipex->cmd_args[index+1] = NULL;
	pipex->cmds[index] = NULL;
	ft_cmd_error_exit(pipex->cmd_args[index][0], pipex);
}

char	*ft_join_path(char *path, t_pipex *pipex, int index)
{
	char	*path_to_cmd;
	char	*cmd_path;

	path_to_cmd = ft_strjoin(path, "/");
	if (!path_to_cmd)
		ft_exit_error("malloc", pipex);
	cmd_path = ft_strjoin(path_to_cmd, pipex->cmd_args[index][0]);
	if (!cmd_path)
	{
		free(path_to_cmd);
		ft_exit_error("malloc", pipex);
	}
	if (path_to_cmd)
		free(path_to_cmd);
	return (cmd_path);
}
