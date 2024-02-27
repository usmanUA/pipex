/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:32:08 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/22 13:46:47 by uahmed           ###   ########.fr       */
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
        ft_exit_error("pipe");
    pid = fork();
    if (pid == -1)
        ft_exit_error("fork");
    dup2(pipex->fd_in, STDIN_FILENO);
    close(pipex->fd_in);
    if (pid == 0)
      ft_child(ft_command(paths, args[2]), fds);
    else
      ft_parent(ft_command(paths, args[3]), fds, args[tot_cmds+3]);
}

void    ft_child(char **cmds, int *fds)
{
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    execve(cmds[0], cmds, NULL);
    ft_exit_error("execve");
}

void    ft_parent(char **cmds, int *fds, char *filename)
{
    pid_t pid;
    int fd;

    pid = fork();
    if (pid == -1)
        ft_exit_error("fork");
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        ft_filerror(filename);
    if (pid == 0)
    {
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execve(cmds[0], cmds, NULL);
        ft_exit_error("execve");
    }
    else
        waitpid(pid, NULL, 0);
}
