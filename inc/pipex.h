/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:34:33 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/08 01:47:11 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_commands
{
	char	*cmd1;
	char	**args1;
	char	*cmd2;
	char	**args2;
	char	**path;
	int		out_fd;
	int		bad_in;
	int		bad_out;
	int		ext_val;
}				t_commands;

void	ft_exit(t_commands *cmd, const char *message, int bad_params, \
	int ext_val);
void	ft_free_cmd(t_commands *cmd);
void	ft_check_params(int argc, char *argv[], char *envp[], t_commands *cmd);
void	ft_parse_args(char *argv[], char *env[], t_commands *cmd);
void	ft_free_2d_char_ptr(char ***ptr);
char	**ft_split_with_quote(char const *s, char c);
void	ft_exec_cmd(t_commands *cmd, char *argv[], char *envp[]);
int		ft_check_odd_nbr_quotes(const char *s);
#endif