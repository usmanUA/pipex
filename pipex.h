/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/22 13:03:14 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "unistd.h"
#include "libft/libft.h"
#include "stdio.h"
#include "fcntl.h"

void    ft_execute(int tot_cmds, char **args, char **envp, int fd);
void    ft_child(char **cmds, int *fds);
void    ft_parent(char **cmds, int *fds, char *filename);
int ft_all_absolute(char *cmds[], int tot_cmds);
char **ft_paths(char *cmds[], char **envp, int tot_cmds);
void    ft_free(char **s);


void    ft_filerror(char *filename);
void    ft_exit_error(char *error_cause);

#endif