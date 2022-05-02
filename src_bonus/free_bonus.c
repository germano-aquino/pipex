/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:08:48 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/01 23:50:51 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	ft_free_2d_char_ptr(char ***ptr)
{
	char	**temp;
	int		i;

	temp = *ptr;
	i = 0;
	while (*temp != NULL)
	{
		free(*temp);
		*temp = NULL;
		i++;
		temp = (*ptr + i);
	}
	free(*ptr);
	*ptr = NULL;
}

void	ft_free_cmd(t_commands *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->n_cmd)
	{
		if (cmd->cmd_path[i] != NULL)
			free(cmd->cmd_path[i]);
		if (cmd->args[i] != NULL)
			ft_free_2d_char_ptr(&cmd->args[i]);
	}
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	if (cmd->args != NULL)
		free(cmd->args);
	if (cmd->cmd_path != NULL)
		free(cmd->cmd_path);
	if (cmd->path != NULL)
		ft_free_2d_char_ptr(&cmd->path);
}
