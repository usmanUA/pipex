/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ipnut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:05:21 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/27 14:07:14 by uahmed           ###   ########.fr       */
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
  char *path;

  path = NULL;
  while (*envp)
    {
      if (!ft_strncmp(*envp, "PATH=", 5))
      {
        path  = *envp;
        break ;
      }
      envp++;
    }
  return (&path[5]);
}

void	ft_save_commands(char **args, char **envp, t_pipex *pipex)
{
  int i;
  char **cmd;

  i = -1;
  cmd = NULL;
  pipex->cmds = (char **)malloc(pipex->tot_cmds * sizeof(char *) + 1);
  pipex->paths = ft_split(ft_give_path(envp), ':');
  while (++i < pipex->tot_cmds)
    {
      cmd = ft_split(args[i+2], ' ');
      if (ft_absolute_path(cmd[0]))
      {
        if (!access(cmd[0], F_OK | X_OK))
          pipex->cmds[i] = cmd[0];
        else
          {
            pipex->cmds[i] = NULL;
            ft_cmderror(cmd[0]);
          }
        ft_free(cmd);
      }
      else
	      pipex->cmds[i] = ft_valid_command(&cmd, pipex);
    }
  pipex->cmds[pipex->tot_cmds] = NULL;
}

char	*ft_valid_command(char ***cmd, t_pipex *pipex)
{
  char *cmd_path;
  int i;

  i = 0;
  cmd_path = NULL;
  while (pipex->paths[i])
    {
      cmd_path = ft_join_path(pipex->paths[i], cmd, pipex);
      i++;
      if (!access(cmd_path, F_OK | X_OK))
        return (cmd_path);
      if (pipex->paths[i])
        free(cmd_path);
    }
  if (cmd_path)
  {
    ft_cmderror(cmd_path);
    free(cmd_path);
  }
  return (NULL);
}

char	*ft_join_path(char *path, char ***cmd, t_pipex *pipex)
{
  char *path_to_cmd;
  char *cmd_path;

  path_to_cmd = ft_strjoin(path, "/");
  if (!path_to_cmd)
    ft_malloc_error(pipex);
  cmd_path = ft_strjoin(path_to_cmd, (*cmd)[0]);
  if (!cmd_path)
  {
    ft_free(*cmd);
    free(path_to_cmd);
    ft_malloc_error(pipex);
  }
  // ft_free(*cmd);
  if (path_to_cmd)
    free(path_to_cmd);
  return (cmd_path);
}
