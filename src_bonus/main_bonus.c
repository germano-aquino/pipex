/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:34:43 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/08 02:16:43 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

t_commands	ft_init_cmd(int argc, char *argv[], t_commands *cmd)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
		cmd->n_cmd = argc - 4;
	else
		cmd->n_cmd = argc - 3;
	cmd->cmd_path = (char **)malloc(sizeof(char *) * (cmd->n_cmd + 1));
	cmd->args = (char ***)malloc(sizeof(char **) * (cmd->n_cmd + 1));
	if (cmd->cmd_path == NULL || cmd->args == NULL)
		ft_exit(cmd, "Allocation error.\n", NULL, 1);
	cmd->args[cmd->n_cmd] = NULL;
	cmd->cmd_path[cmd->n_cmd] = NULL;
	cmd->path = NULL;
	cmd->bad_in = 0;
	cmd->out_fd = -1;
	cmd->bad_out = 0;
	cmd->inval_cmd_flag = 0;
	cmd->ext_val = 0;
	cmd->is_hd = 0;
	return (*cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_commands	cmd;

	if (argc < 5)
		ft_exit(NULL, "Number of parameters is wrong.\n", NULL, 0);
	cmd = ft_init_cmd(argc, argv, &cmd);
	cmd.is_hd = ft_here_doc(&cmd, argv, argc);
	ft_check_params(argc, argv, envp, &cmd);
	ft_parse_args(argv, envp, &cmd);
	ft_exec_cmds(&cmd, argv, envp);
	ft_exit(&cmd, NULL, NULL, cmd.ext_val);
	return (0);
}

void	ft_exit(t_commands *cmd, const char *message, char **vars, int ext_val)
{
	int	last_cmd_not_exist;

	if (cmd != NULL)
	{
		last_cmd_not_exist = cmd->inval_cmd_flag & 1 << (cmd->n_cmd - 1);
		if (cmd->bad_out)
			ext_val = 1;
		else if (last_cmd_not_exist)
			ext_val = 127;
		ft_free_cmd(cmd);
	}
	if (message != NULL)
	{
		ft_printf("%s", message);
		if (vars != NULL)
			ft_free_2d_char_ptr(&vars);
	}
	exit(ext_val);
}
