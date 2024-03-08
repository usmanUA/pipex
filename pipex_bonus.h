/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 11:56:33 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "fcntl.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "pipex.h"
# include "stdio.h"
# include "sys/wait.h"
# include "unistd.h"

int	ft_execute_bonus(t_pipex *ppx, char **envp);
void	ft_processes(t_pipex *pipex, int ind, char **envp);

#endif
