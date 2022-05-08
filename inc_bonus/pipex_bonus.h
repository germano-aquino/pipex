/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:34:33 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/08 02:08:07 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_workspace
{
	int	curr_fd;
	int	fd[2];
	int	i;
}				t_workspace;

typedef struct s_commands
{
	char	**cmd_path;
	char	***args;
	char	**path;
	char	**envp;
	char	*limiter;
	int		out_fd;
	int		inval_cmd_flag;
	int		bad_in;
	int		bad_out;
	int		is_hd;
	int		n_cmd;
	int		ext_val;
}				t_commands;

void	ft_exit(t_commands *cmd, const char *message, char **vars, int ext_val);
void	ft_free_cmd(t_commands *cmd);
void	ft_check_params(int argc, char *argv[], char *envp[], t_commands *cmd);
void	ft_parse_args(char *argv[], char *env[], t_commands *cmd);
void	ft_free_2d_char_ptr(char ***ptr);
char	**ft_split_with_quote(char const *s, char c);
void	ft_exec_cmds(t_commands *cmd, char *argv[], char *envp[]);
int		ft_check_odd_nbr_quotes(const char *s);
int		ft_here_doc(t_commands *cmd, char *argv[], int argc);
char	**ft_get_enviroment(char *envp[]);
#endif