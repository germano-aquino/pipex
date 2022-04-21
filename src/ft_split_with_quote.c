/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:46:36 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/12 22:37:05 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pipex.h>

static int	ft_get_number_of_strings(const char *s, char c)
{
	int	counter;
	int	new_string_was_counted;
	int	i;

	counter = 0;
	i = 0;
	new_string_was_counted = 0;
	if (ft_check_odd_nbr_quotes(s))
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			while (s[i + 1] != '\'' && s[i + 1] != '\0')
				i++;
		if (!new_string_was_counted && s[i] != c)
		{
			counter++;
			new_string_was_counted = 1;
		}
		if (new_string_was_counted && s[i] == c)
			new_string_was_counted = 0;
		i++;
	}
	return (counter);
}

static int	ft_get_valid_indexes(char const *s, char c, int *indexes)
{
	int	index;
	int	nb_quotes;

	nb_quotes = 0;
	index = indexes[0];
	while (s[index] == c)
		index++;
	indexes[0] = index;
	while (s[index] != c && s[index] != '\0')
	{
		if (s[index] == '\'')
		{
			nb_quotes += 2;
			index++;
			while (s[index] != '\'')
				index++;
		}
		index++;
	}
	indexes[1] = index - 1;
	return (nb_quotes);
}

static void	ft_copy_string_to_ptr(char const *s, int *indexes, char *ptr)
{
	int	i;
	int	quote_escape;

	quote_escape = 0;
	i = 0;
	while (i < indexes[1] - indexes[0] + 1 - quote_escape)
	{
		if (s[indexes[0] + i + quote_escape] == '\'')
			quote_escape++;
		ptr[i] = s[indexes[0] + i + quote_escape];
		i++;
	}
	ptr[i] = '\0';
	indexes[0] = indexes[1] + 1;
}

static void	ft_variables_initiation(int *indexes)
{
	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
}

	//ind[] is a vector of indexes where
	//ind[0] is the start index of the string to be splitted
	//ind[1] is the end index of the string to be splitted
	//ind[2] is a iterable index of split
char	**ft_split_with_quote(char const *s, char c)
{
	int		ind[3];
	int		n_str;
	int		n_quotes;
	char	**split;

	ft_variables_initiation(ind);
	n_str = ft_get_number_of_strings(s, c);
	split = (char **) malloc(sizeof(char *) * (n_str + 1));
	if (split == NULL || n_str == -1)
		return (0);
	split[0] = NULL;
	while (ind[2] < n_str)
	{
		n_quotes = ft_get_valid_indexes(s, c, ind);
		split[ind[2]] = (char *)malloc(ind[1] - ind[0] + 2 - n_quotes);
		if (split[ind[2]] == NULL)
		{
			free(split);
			return (0);
		}
		ft_copy_string_to_ptr(s, ind, split[ind[2]]);
		ind[2]++;
	}
	split[ind[2]] = NULL;
	return (split);
}
