/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:03:12 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/26 12:03:40 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "execute.h"

static size_t
	take_size(char *str, char delimiter)
{
	size_t	size;
	int		i;

	size = 0;
	i = -1;
	while (str[++i])
	{
		if (s[i] == delimiter)
			size++;
	}
	if (size)
		size++;
	return (size);
}

static void
	*free_memory(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
	return (NULL);
}

static void
	copy_value(char **value, char **str, int word_len)
{
	if (word_len)
	{
		ft_strlcpy(*value, *str, word_len + 1);
		*str += word_len;
	}
	else
		ft_strlcpy(*value, ".", 2);
	if ((*str)[0])
		(*str)++;
}

static char
	**create_values(char *str, char delimiter, size_t count)
{
	char	**values;
	int		word_len;
	int		i;

	values = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!values)
		error_exit(NULL);
	i = 0;
	values[count] = NULL;
	while (count--)
	{
		word_len = 0;
		while (str[word_len] && str[word_len] != delimiter)
			word_len++;
		if (word_len)
			values[i] = (char *)ft_calloc(word_len + 1, sizeof(char));
		else
			values[i] = (char *)ft_calloc(2, sizeof(char));
		if (!values[i])
			return (free_memory(values, i));
		copy_value(&values[i], &str, word_len);
		i++;
	}
	return (values);
}

char
	**split_value(char *value, char delimiter)
{
	char			**values;
	size_t			count;

	count = take_size(value, delimiter);
	values = create_values(value, delimiter, count);
	return (values);
}
