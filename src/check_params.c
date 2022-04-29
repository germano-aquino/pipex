/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:34:40 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/24 00:32:03 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	cmd_path = ft_strjoin(".", cmd);
	if (!access(cmd_path, F_OK | X_OK))
		return (cmd_path);
	free(cmd_path);
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

	if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror(argv[1]);
		cmd->bad_in = 1;
		if (access(argv[1], F_OK) == -1)
			cmd->ext_val = 1;
	}
	if (access(argv[argc - 1], F_OK | W_OK) == -1)
	{
		fd = open(argv[argc - 1], O_CREAT, 0666);
		if (fd == -1 || access(argv[argc - 1], W_OK) == -1)
		{
			perror(argv[argc - 1]);
			cmd->bad_out = 1;
			cmd->ext_val = 1;
		}
		close(fd);
	}
}

int	ft_check_cmd_exists(char *argv, char *path[], char **cmd_path, \
	t_commands *cmd)
{
	char	**split;
	char	*temp;

	split = ft_split(argv, ' ');
	temp = ft_strjoin("/", split[0]);
	*cmd_path = ft_get_cmd_path(path, temp);
	if (*cmd_path == NULL)
	{
		free(temp);
		ft_printf("%s: command not found\n", split[0]);
		ft_free_2d_char_ptr(&split);
		return (0);
	}
	free(temp);
	ft_free_2d_char_ptr(&split);
	return (1);
}

void	ft_check_params(int argc, char *argv[], char *envp[], t_commands *cmd)
{
	if (argc != 5)
		ft_exit(cmd, "Number of parameters is wrong.\n", 1, 0);
	cmd->path = ft_get_path(envp);
	if (cmd->path == NULL)
		ft_exit(cmd, "Environment variable PATH does not exist.\n", 1, 1);
	ft_check_file_exists(argc, argv, cmd);
	if (!ft_check_cmd_exists(argv[2], cmd->path, &cmd->cmd1, cmd))
		cmd->ext_val = 0;
	if (!ft_check_cmd_exists(argv[3], cmd->path, &cmd->cmd2, cmd))
		cmd->ext_val = 127;
}
