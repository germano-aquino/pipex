/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:08:48 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:02:59 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	if (cmd->cmd1 != NULL)
		free(cmd->cmd1);
	if (cmd->cmd2 != NULL)
		free(cmd->cmd2);
	if (cmd->args1 != NULL)
		ft_free_2d_char_ptr(&cmd->args1);
	if (cmd->args2 != NULL)
		ft_free_2d_char_ptr(&cmd->args2);
	if (cmd->path != NULL)
		ft_free_2d_char_ptr(&cmd->path);
}
