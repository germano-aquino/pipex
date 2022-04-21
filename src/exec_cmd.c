/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:32:23 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/20 23:12:30 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_exec_second_cmd(t_commands *cmd, int fd[2], char *argv[])
{
	int	out_fd;

	close(fd[1]);
	out_fd = open(argv[4], O_WRONLY);
	dup2(out_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(out_fd);
	execve(cmd->cmd2, cmd->args2, NULL);
}

void	ft_exec_first_cmd(t_commands *cmd, int fd[2], char *argv[])
{
	int	in_fd;

	close(fd[0]);
	in_fd = open(argv[1], O_RDONLY);
	dup2(in_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(in_fd);
	execve(cmd->cmd1, cmd->args1, NULL);
}

void	ft_exec_cmd(t_commands *cmd, char *argv[])
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		ft_exit(cmd, "Cannot create pipe.\n", NULL, 1);
	if (!cmd->err && fork() == 0)
		ft_exec_first_cmd(cmd, fd, argv);
	wait(NULL);
	if ((!cmd->err || cmd->ext_val != 127) && fork() == 0)
		ft_exec_second_cmd(cmd, fd, argv);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
}
