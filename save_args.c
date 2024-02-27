
#include "pipex.h"

void	ft_save_args(char **args, t_pipex *pipex)
{
  int i;

  i = -1;
  pipex->cmd_args = (char ***)malloc(pipex->tot_cmds * sizeof(char **));
  if (!pipex->cmd_args)
    ft_malloc_error(pipex);
  while (++i < pipex->tot_cmds)
    pipex->cmd_args[i] = ft_split(args[i], ' ');
}
