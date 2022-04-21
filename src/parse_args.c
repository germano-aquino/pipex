/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:46:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:01:49 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	cmd->args1 = ft_split_with_quote(argv[2], ' ');
	cmd->args2 = ft_split_with_quote(argv[3], ' ');
}
