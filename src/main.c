/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:34:43 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/08 02:18:52 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_init_cmd(t_commands *cmd)
{
	cmd->cmd1 = NULL;
	cmd->cmd2 = NULL;
	cmd->args1 = NULL;
	cmd->args2 = NULL;
	cmd->path = NULL;
	cmd->out_fd = 0;
	cmd->bad_in = 0;
	cmd->bad_out = 0;
	cmd->ext_val = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_commands	cmd;

	ft_init_cmd(&cmd);
	ft_check_params(argc, argv, envp, &cmd);
	ft_parse_args(argv, envp, &cmd);
	ft_exec_cmd(&cmd, argv, envp);
	ft_exit(&cmd, NULL, 0, cmd.ext_val);
	return (0);
}

void	ft_exit(t_commands *cmd, const char *message, int bad_params, \
	int ext_val)
{
	if (cmd != NULL)
	{
		if (cmd->bad_out)
			ext_val = 1;
		else if (cmd->cmd2 == NULL && !bad_params)
			ext_val = 127;
		ft_free_cmd(cmd);
	}
	if (message != NULL)
		ft_printf("%s", message);
	exit(ext_val);
}
