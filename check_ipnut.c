

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
  char **paths;
  int i;
  char *cmd;
  char **temp;

  i = -1;
  pipex->cmds = (char **)malloc(pipex->tot_cmds * sizeof(char *) + 1);
  paths = ft_split(ft_give_path(envp), ':');
  while (++i < pipex->tot_cmds)
    {
      cmd = ft_split(args[i+2], ' ')[0];
      if (ft_absolute_path(cmd))
      {
        // write(1, "here\n", 5);
        if (!access(cmd, F_OK | X_OK))
          pipex->cmds[i] = cmd;
        else
          {
            pipex->cmds[i] = NULL;
            ft_cmderror(cmd);
          }
      }
      else
      {
        // write(1, "here\n", 5);
	      pipex->cmds[i] = ft_valid_command(cmd, &paths, pipex);
      }
    }
  pipex->cmds[pipex->tot_cmds] = NULL;
}

char	*ft_valid_command(char *arg, char ***paths, t_pipex *pipex)
{
  char *cmd;
  int i;
  int flag;

  i = -1;
  flag = 0;
  while (*(paths)[++i])
    {
      cmd = ft_join_path(*(paths)[i], arg, pipex);
      printf("final cmd: %s\n", cmd);
      if (!access(cmd, F_OK | X_OK))
      {
        flag = 0;
        write(1, "here\n", 5);
        ft_free(*paths);
        return (cmd);
      }
    }
    if (flag)
    {
      ft_cmderror(cmd);
      free(cmd);
      cmd = NULL;
    }
  ft_free(*paths);
  return (NULL);
}

char	*ft_join_path(char *path, char *arg, t_pipex *pipex)
{
  char *half_cmd;
  char *cmd;

  half_cmd = ft_strjoin(path, "/");
  if (!half_cmd)
    ft_malloc_error(pipex);
  cmd = ft_strjoin(half_cmd, arg);
  if (!cmd)
    ft_malloc_error(pipex);
  free(half_cmd);
  return (cmd);
}
