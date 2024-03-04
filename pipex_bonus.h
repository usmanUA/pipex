/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/01 14:52:41 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"
# include "fcntl.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "stdio.h"
# include "sys/wait.h"
# include "unistd.h"


void	ft_print_pipex(t_pipex *pipex);

void	ft_execute_bonus(t_pipex *pipex);
void	ft_processes(t_pipex *pipex, int ind);


#endif
