/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:32:23 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/02 00:12:03 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	ft_here_doc(t_commands *cmd, char *argv[], int argc)
{
	char	*line;
	int		fd[2];

	if (!ft_strncmp(argv[1], "here_doc", 9) && argc > 5)
	{
		if (pipe(fd) == -1)
			ft_exit(cmd, "Cannot create pipe.\n", NULL, 1);
		while (1)
		{
			ft_printf("> ");
			line = get_next_line(STDIN_FILENO, 0);
			if (!ft_strncmp(line, argv[2], ft_strlen(line) - 1) \
				&& line[ft_strlen(line) - 1] == '\n')
			{
				close(fd[1]);
				free(line);
				line = get_next_line(STDIN_FILENO, 1);
				return (fd[0]);
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	return (0);
}

void	child_task(t_commands *cmd, int i, int *pipe_fd, int *curr_fd)
{
	int	out_fd;

	dup2(*curr_fd, STDIN_FILENO);
	close(pipe_fd[0]);
	if ((!cmd->err && !i) || (i && (!cmd->err || cmd->ext_val != 127)))
	{
		if (i == cmd->n_cmd - 1)
		{
			close(pipe_fd[1]);
			out_fd = open(cmd->outfile, O_WRONLY);
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		else
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		if (execve(cmd->cmd_path[i], cmd->args[i], NULL) == -1)
			ft_exit(cmd, "Cannot exec command.\n", NULL, 1);
	}
	close(pipe_fd[1]);
	ft_exit(cmd, NULL, NULL, 1);
}

void	ft_exec_cmd(t_commands *cmd, char *argv[], int i, int *curr_fd)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		ft_exit(cmd, "Cannot create pipe.\n", NULL, 1);
	if (*curr_fd == -1)
		*curr_fd = fd[0];
	pid = fork();
	if (pid == 0)
		child_task(cmd, i, fd, curr_fd);
	else
	{
		close(*curr_fd);
		dup2(fd[0], *curr_fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, &cmd->ext_val, WNOHANG);
	}
}

void	ft_exec_cmds(t_commands *cmd, char *argv[])
{
	int	curr_fd;
	int	i;
	int	flag;

	i = -1;
	if (cmd->is_hd)
		curr_fd = cmd->is_hd;
	else
		curr_fd = open(argv[1], O_RDONLY);
	while (++i < cmd->n_cmd)
	{
		flag = cmd->inval_cmd_flag & (1 << i);
		if (!i && cmd->bad_in || flag)
			curr_fd = -1;
		else if (!flag && !(i == cmd->n_cmd - 1 && cmd->bad_out))
			ft_exec_cmd(cmd, argv, i, &curr_fd);
	}
	cmd->ext_val = WEXITSTATUS(cmd->ext_val);
	close(curr_fd);
}
