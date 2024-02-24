/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:48:54 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/22 13:02:52 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char **envp)
{
    int fd;
    
    if (argc > 1)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            ft_filerror(argv[1]);
        ft_execute(argc - 3, &argv[2], envp, fd);
    }
    return (0);
}