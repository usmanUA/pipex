/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:51:13 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/22 13:04:34 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_free(char **s)
{
    int i;
    
    i = -1;
    if (s)
    {
        while (s[++i])
            free(s[i]);
        s = NULL;
    }
}


char **ft_paths(char *cmds[], char **envp, int tot_cmds)
{
    char **paths;
    int i;

    paths = NULL;
    i = -1;
    
    if (ft_all_absolute(cmds, tot_cmds))
        return (NULL);
    while (*envp)
    {
        if (!ft_strncmp(*envp, "PATH=", 5))
        {    
            paths = ft_split(&(*envp)[5], ':');
            if (!paths)
                exit(EXIT_FAILURE);
            return (paths);
        }
        envp++;
    }
    return (paths);
    
}

int ft_all_absolute(char *cmds[], int tot_cmds)
{
    int i;

    i = -1;
    while (++i < tot_cmds)
    {
        if (!ft_strncmp(cmds[i], "/", 1) || !ft_strncmp(cmds[i], "./", 2))
            continue ;
        else
            return (0);
    }
    return (1);
}

