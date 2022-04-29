/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:32:23 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/24 00:36:48 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_exec_second_cmd(t_commands *cmd, int fd[2], char *argv[], \
	char *envp[])
{
	int	out_fd;

	close(fd[1]);
	out_fd = open(argv[4], O_WRONLY);
	dup2(out_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(out_fd);
	execve(cmd->cmd2, cmd->args2, envp);
}

void	ft_exec_first_cmd(t_commands *cmd, int fd[2], char *argv[], \
	char *envp[])
{
	int	in_fd;

	close(fd[0]);
	in_fd = open(argv[1], O_RDONLY);
	dup2(in_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(in_fd);
	execve(cmd->cmd1, cmd->args1, envp);
}

void	ft_exec_cmd(t_commands *cmd, char *argv[], char *envp[])
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		ft_exit(cmd, "Cannot create pipe.\n", 1, 1);
	if (!cmd->bad_in && cmd->cmd1 != NULL && fork() == 0)
		ft_exec_first_cmd(cmd, fd, argv, envp);
	if (!cmd->bad_out && cmd->cmd2 != NULL && fork() == 0)
		ft_exec_second_cmd(cmd, fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	wait(&cmd->ext_val);
	cmd->ext_val = WEXITSTATUS(cmd->ext_val);
}
