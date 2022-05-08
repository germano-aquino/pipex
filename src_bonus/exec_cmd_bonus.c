/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:32:23 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/08 02:24:00 by grenato-         ###   ########.fr       */
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

void	child_task(t_commands *cmd, t_workspace *vars, char *envp[])
{
	dup2(vars->curr_fd, STDIN_FILENO);
	close(vars->fd[0]);
	if (vars->i == cmd->n_cmd - 1)
	{
		close(vars->fd[1]);
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	else
	{
		dup2(vars->fd[1], STDOUT_FILENO);
		close(vars->fd[1]);
	}
	if (execve(cmd->cmd_path[vars->i], cmd->args[vars->i], envp) == -1)
		ft_exit(cmd, "Cannot exec command.\n", NULL, 1);
	close(vars->fd[1]);
	ft_exit(cmd, NULL, NULL, 1);
}

void	ft_exec_cmd(t_commands *cmd, char *argv[], char *envp[], \
			t_workspace *vars)
{
	int	pid;

	if (pipe(vars->fd) == -1)
		ft_exit(cmd, "Cannot create pipe.\n", NULL, 1);
	if (vars->curr_fd == -1)
		vars->curr_fd = vars->fd[0];
	pid = fork();
	if (pid == 0)
		child_task(cmd, vars, envp);
	else
	{
		close(vars->curr_fd);
		dup2(vars->fd[0], vars->curr_fd);
		close(vars->fd[0]);
		close(vars->fd[1]);
	}
}

void	ft_exec_cmds(t_commands *cmd, char *argv[], char *envp[])
{
	t_workspace	vars;
	int			flag;

	vars.i = -1;
	if (cmd->is_hd)
		vars.curr_fd = cmd->is_hd;
	else
		vars.curr_fd = open(argv[1], O_RDONLY);
	while (++vars.i < cmd->n_cmd)
	{
		flag = cmd->inval_cmd_flag & (1 << vars.i);
		if (!vars.i && (cmd->bad_in || flag))
			vars.curr_fd = -1;
		else if (!flag && !(vars.i == (cmd->n_cmd - 1) && cmd->bad_out))
			ft_exec_cmd(cmd, argv, envp, &vars);
	}
	wait(&cmd->ext_val);
	cmd->ext_val = WEXITSTATUS(cmd->ext_val);
	close(vars.curr_fd);
}
