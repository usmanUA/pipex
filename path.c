/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:51:13 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/27 12:45:30 by uahmed           ###   ########.fr       */
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
	free(s);
    }
}

int ft_absolute_path(char *cmd)
{
  if (!ft_strncmp(cmd, "/", 1) || !ft_strncmp(cmd, "./", 2))
    return (1);
  return (0);
}
