/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:34:43 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:00:52 by grenato-         ###   ########.fr       */
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
	cmd->err = 0;
	cmd->ext_val = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_commands	cmd;

	ft_init_cmd(&cmd);
	ft_check_params(argc, argv, envp, &cmd);
	ft_parse_args(argv, envp, &cmd);
	ft_exec_cmd(&cmd, argv);
	ft_exit(&cmd, NULL, NULL, cmd.ext_val);
	return (0);
}

void	ft_exit(t_commands *cmd, const char *message, char **vars, int ext_val)
{
	if (cmd != NULL)
		ft_free_cmd(cmd);
	if (message != NULL)
	{
		ft_printf("%s", message);
		if (vars != NULL)
			ft_free_2d_char_ptr(&vars);
	}
	exit(ext_val);
}
