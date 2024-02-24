/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:00:14 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/22 10:51:41 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int main(int argc, char *argv[], char **envp)
{
    int fds[argc - 3][2];
    int pipes[argc - 3];
    pid_t pids[argc - 3];
    int i;
    int fd;
    int rb;
    char buff[256];
    char *hlf_path;
    char *path;
    char **paths;
    char *program;
    char **cmd;
    char **tmp;

    i = -1;
    if (argc > 1)
    {
        paths = ft_paths(envp);
        while (++i < argc - 3)
        {
            program = NULL;
            cmd = ft_split(argv[2+i], ' ');
            tmp = paths;
            while (*tmp)
            {
                hlf_path = NULL;
                path = NULL;
                hlf_path = ft_strjoin(*tmp, "/");
                path = ft_strjoin(hlf_path, argv[2+i]);
                if (!access(path, F_OK | X_OK))
                {
                    program = path;
                    if (hlf_path)
                        free(hlf_path);
                    break ;
                }
                if (path)
                    free(path);
                if (hlf_path)
                    free(hlf_path);
                tmp++;
            }
            ft_free(paths);
            if (!program)
            {
                printf("zsh: command not found: %s\n", argv[1]);
                ft_free(cmd);
                exit(EXIT_FAILURE);
            }
             // create pipes for each command
            pipes[i] = pipe(fds[i]);
            if (pipes[i] == -1)
            {
                perror("pipe");
                ft_free(cmd);
                if (program)
                    free(program);
                exit(EXIT_FAILURE);
            }
            // create pipes for each command
            pids[i] = fork();
            if (pids[i] == -1)
            {
                perror("fork");
                ft_free(cmd);
                if (program)
                    free(program);
                exit(EXIT_FAILURE);
            }
            if (pids[i] == 0)
            {
                close(fds[i][1]); // Close the write end of the pipe for current child
                if (i != argc - 3) // not the last processs
                {
                    dup2(fds[i][0], STDIN_FILENO); // duplicate current pipe's read end to std input
                    close(fds[i][0]);
                    dup2(fds[i+1][1], STDOUT_FILENO); // duplicate next pipe's write end to std output
                    close(fds[i+1][1]);
                    execve(program, cmd, envp);
                    if (program)
                        free(program);
                    ft_free(cmd);
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    // dup2(fds[i][1], STDOUT_FILENO);
                    // close(fds[i][0]);
                    dup2(fds[i][0], STDIN_FILENO);
                    execve(program, cmd, envp);
                    if (program)
                        free(program);
                    ft_free(cmd);
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
        }
        i = -1;
        // while (++i < argc - 1)
        close(fds[0][0]);
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            printf("zsh: no such file or directory: %s\n", argv[1]);
            if (paths)
                ft_free(paths);
            exit(EXIT_FAILURE);
        }
        rb = 1;
        dup2(fd, STDIN_FILENO);
        close(fd);
        i = -1;
        while (++i < argc - 3)
            waitpid(pids[i], NULL, 0);
        ft_free(paths);
        return (0);
    }
}


//         close(fds[1]);
//         dup2(fds[0], STDIN_FILENO);
//         execve(program, cmd, envp);
//         perror("execve");
//         exit(1);
//         if (fd == -1)
//         {
//             return (1);
//         }
//         wait(NULL);
//         ft_free(cmd);
//         close(fd);
//         }
//     }
//     return (0);
// }
