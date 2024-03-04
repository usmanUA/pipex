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

void	ft_validate_files(char *infile, char *outfile, t_pipex *pipex)
{

	pipex->fd_in = open(infile, O_RDONLY);
	if (pipex->fd_in == -1)
		ft_filerror(infile);
	pipex->fd_out = open(outfile, O_WRONLY | O_CREAT| O_APPEND, 0644);
	if (pipex->fd_out == -1)
		ft_filerror(outfile);
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
	int i;

	i = -1;
	ft_malloc_struct(pipex, &pipex->cmds, &pipex->cmd_args);
	pipex->paths = ft_split(ft_give_path(envp), ':');
	while (++i < pipex->tot_cmds)
	{
		pipex->cmd_args[i] = ft_split(args[i + pipex->start], ' ');
		if (ft_absolute_path(pipex->cmd_args[i][0]))
		{
			if (!access(pipex->cmd_args[i][0], F_OK | X_OK))
				pipex->cmds[i] = ft_strdup(pipex->cmd_args[i][0]);
			else
			{
				pipex->cmds[i] = NULL;
				ft_cmd_error_exit(pipex->cmd_args[i][0], pipex);
			}
		}
		else
			ft_valid_command(pipex, i);
	}
	pipex->cmds[i] = NULL;
	pipex->cmd_args[i] = NULL;	
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
