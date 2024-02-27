/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:32:08 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/27 12:17:15 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_execute(t_pipex *pipex)
{
    int fds[2];
    int pips;
    pid_t pid;
    
    pips = pipe(fds);
    if (pips == -1)
      ft_exit_error("pipe", pipex);
    pid = fork();
    if (pid == -1)
      ft_exit_error("fork", pipex);
    dup2(pipex->fd_in, STDIN_FILENO);
    close(pipex->fd_in);
    
    if (pid == 0)
    {
      close(fds[0]);
      ft_child(pipex, fds);
    }
    else
    {
      close(fds[1]);
      ft_parent(pipex, fds);
    }
}

void    ft_child(t_pipex *pipex, int *fds)
{
    
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    execve(pipex->cmds[0], pipex->cmd_args[0], NULL);
    ft_exit_error("execve", pipex);
}

void    ft_parent(t_pipex *pipex, int *fds)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
      ft_exit_error("fork", pipex);
    if (pid == 0)
    {
        
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        dup2(pipex->fd_out, STDOUT_FILENO);
        close(pipex->fd_out);
        execve(pipex->cmds[1], pipex->cmd_args[1], NULL);
        ft_exit_error("execve", pipex);
    }
    else
        waitpid(pid, NULL, 0);
}
