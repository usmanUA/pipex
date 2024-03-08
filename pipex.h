/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:49:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/08 15:28:31 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "stdio.h"
# include "sys/wait.h"
# include "unistd.h"
# include "errno.h"
# include "string.h"

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_pipex
{
	int		fd_in;
	int		fdin_failed;
	int		fd_out;
	int fdout_failed;
	int		start;
	int		idx;
	t_bool	here_doc;
	char	**paths;
	char	**cmds;
	char	***cmd_args;
	int		tot_cmds;
}			t_pipex;

void		ft_print_pipex(t_pipex *pipex);

void		ft_free_pipex(t_pipex *pipex);
void		ft_initialize_pipex(t_pipex *pipex, int tot_cmds);

int	ft_execute(t_pipex *pipex, char **envp);
void	ft_first_child(t_pipex *pipex, int *fds, char **envp);
void	ft_second_child(t_pipex *pipex, int *fds, int *status, char **envp);
int	ft_pair_failed(t_pipex *pipex, int cmd_num, int i);
int	ft_failure_status(int file_status, char *cmd);
int	ft_status(int status);


char		**ft_paths(char *cmds[], char **envp, int tot_cmds);

void		ft_validate_files(char *infile, char *outfile, t_pipex *pipex);
char		*ft_give_path(char **envp);
void		ft_save_commands(char **args, char **envp, t_pipex *pipex);
void		ft_valid_command(t_pipex *pipex);
char		*ft_join_path(char *path, t_pipex *pipex);
void		ft_save_args(char **args, t_pipex *pipex);

void	ft_filerror(int errnu, t_pipex *pipex, char *filename, int infile);
void	ft_cmd_error(char *cmd, int permission);
void	ft_exit_error(t_pipex *pipex, int free, int status);

#endif
