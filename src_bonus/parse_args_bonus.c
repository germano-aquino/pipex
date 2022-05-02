/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:46:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/05/01 23:51:39 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	ft_check_odd_nbr_quotes(const char *s)
{
	int	i;
	int	counter;

	if (s == NULL)
		return (1);
	counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			counter++;
		i++;
	}
	return (counter % 2);
}

void	ft_parse_args(char *argv[], char *envp[], t_commands *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->n_cmd)
	{
		if (!cmd->is_hd)
			cmd->args[i] = ft_split_with_quote(argv[i + 2], ' ');
		else
			cmd->args[i] = ft_split_with_quote(argv[i + 3], ' ');
	}
}
