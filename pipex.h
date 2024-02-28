/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/02/28 13:24:35 by uahmed           ###   ########.fr       */
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
	char	**paths;
	char	***temp_cmds;
	char	**cmds;
	char	***cmd_args;
	t_bool	here_doc;
	t_bool	bonus;
	int		tot_cmds;
}			t_pipex;


void	ft_print_pipex(t_pipex *pipex);


void		ft_free(char **s);
void		ft_free_pipex(t_pipex *pipex);
void		ft_initialize_pipex(t_pipex *pipex, int tot_cmds);

void		ft_execute(t_pipex *pipex);
void		ft_child(t_pipex *pipex, int *fds);
void		ft_parent(t_pipex *pipex, int *fds);
int			ft_absolute_path(char *cmd);
char		**ft_paths(char *cmds[], char **envp, int tot_cmds);
void		ft_free(char **s);

void		ft_validate_files(int argc, char **args, t_pipex *pipex);
char		*ft_give_path(char **envp);
void		ft_save_commands(char **args, char **envp, t_pipex *pipex);
char		*ft_valid_command(t_pipex *pipex, char **temp_cmds);
char		*ft_join_path(char *path, t_pipex *pipex, char **temp_cmds);
void		ft_save_args(char **args, t_pipex *pipex);

void		ft_filerror(char *filename);
void		ft_malloc_error(t_pipex *pipex);
void		ft_cmderror(char *cmd);
void		ft_exit_error(char *error_cause, t_pipex *pipex);

#endif
