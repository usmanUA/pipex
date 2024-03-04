/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/01 16:56:50 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "libft/libft.h"
# include "stdio.h"
# include "sys/wait.h"
# include "unistd.h"

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		start;
	char	**paths;
	char	**cmds;
	char	***cmd_args;
	int		tot_cmds;
}			t_pipex;


void	ft_print_pipex(t_pipex *pipex);


void		ft_freestrs(char **s);
void		ft_free_pipex(t_pipex *pipex);
void		ft_initialize_pipex(t_pipex *pipex, int tot_cmds);

void		ft_execute(t_pipex *pipex);
void		ft_child(t_pipex *pipex, int *fds);
void		ft_parent(t_pipex *pipex, int *fds);
int			ft_absolute_path(char *cmd);
char		**ft_paths(char *cmds[], char **envp, int tot_cmds);

void	ft_validate_files(char *infile, char *outfile, t_pipex *pipex);
char		*ft_give_path(char **envp);
void		ft_save_commands(char **args, char **envp, t_pipex *pipex);
void		ft_valid_command(t_pipex *pipex, int i);
char		*ft_join_path(char *path, t_pipex *pipex, int i);
void		ft_save_args(char **args, t_pipex *pipex);

void		ft_filerror(char *filename);
void		ft_cmd_error_exit(char *cmd, t_pipex *pipex);
void		ft_exit_error(char *error_cause, t_pipex *pipex);

#endif
