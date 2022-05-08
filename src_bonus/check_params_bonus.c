/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:34:40 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/08 01:33:07 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

char	**ft_get_path(char *envp[])
{
	char	**path;
	char	**temp;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			break ;
		i++;
	}
	temp = ft_split(envp[i], '=');
	path = ft_split(temp[1], ':');
	ft_free_2d_char_ptr(&temp);
	return (path);
}

char	*ft_get_cmd_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	while (path[i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static void	ft_check_file_exists(int argc, char *argv[], t_commands *cmd)
{
	int	fd;

	if (!cmd->is_hd && access(argv[1], F_OK | R_OK) == -1)
	{
		cmd->bad_in = 1;
		perror(argv[1]);
		if (access(argv[1], F_OK) == -1)
			cmd->bad_in++;
	}
	if (!access(argv[argc - 1], F_OK | W_OK))
		unlink(argv[argc - 1]);
	if (access(argv[argc - 1], F_OK) == -1)
		cmd->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
	if (access(argv[argc - 1], W_OK) == -1 || cmd->out_fd == -1)
	{
		perror(argv[argc - 1]);
		cmd->bad_out = 1;
	}
}

void	ft_check_cmd_exists(char *argv, int i, char **cmd_path, \
	t_commands *cmd)
{
	char	**split;
	char	*temp;

	split = ft_split(argv, ' ');
	temp = ft_strjoin("/", split[0]);
	if (access(split[0], X_OK | F_OK) == 0)
		*cmd_path = ft_strdup(split[0]);
	else
		*cmd_path = ft_get_cmd_path(cmd->path, temp);
	free(temp);
	if (*cmd_path == NULL)
	{
		cmd->inval_cmd_flag |= 1 << i;
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	ft_free_2d_char_ptr(&split);
}

void	ft_check_params(int argc, char *argv[], char *envp[], t_commands *cmd)
{
	int	i;

	cmd->path = ft_get_path(envp);
	if (cmd->path == NULL)
		ft_exit(cmd, "Environment variable PATH does not exist.\n", NULL, 1);
	ft_check_file_exists(argc, argv, cmd);
	i = -1;
	while (++i < cmd->n_cmd)
	{
		if (!cmd->is_hd)
			ft_check_cmd_exists(argv[2 + i], i, &cmd->cmd_path[i], cmd);
		else
			ft_check_cmd_exists(argv[3 + i], i, &cmd->cmd_path[i], cmd);
	}
}
