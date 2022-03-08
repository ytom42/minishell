/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:48:00 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/08 14:06:44 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int get_token_size(char *line, int *i)
{
	int		size;
	int dq;
	int sq;

	size = 0;
	dq = 0;
	sq = 0;
	if (line[*i] == '>' || line[*i] == '<')
	{
		size += 1;
		if (line[*i] == '>' && line[*i + 1] == '>')
			size += 1;
		else if (line[*i] == '<' && line[*i + 1] == '<')
			size += 1;
		return (size);
	}
	else if (line[*i] == '|')
	{
		size += 1;
		return (size);
	}
	else
	{
		if (line[*i] == '"')
		{
			dq = 1;
			size += 1;
		}
		else if (line[*i] == '\'')
		{
			sq = 1;
			size += 1;
		}
		while (line[*i + size])
		{
			if (dq == 0 && sq == 0 && is_delimiter(line[*i + size]))
				break ;
			if (dq && line[*i + size] == '"')
			{
				size++;
				break ;
			}
			if (sq && line[*i + size] == '\'')
			{
				size++;
				break ;
			}
			size += 1;
		}
		return (size);
	}
}

t_token	*get_token(char *line, int *i)
{
	int		size;
	char	*str;
	t_token	*new_token;

	size = 0;
	skip_space(line, i);
	size = get_token_size(line, i);
	if (size == 0)
		return (NULL);
	str = ft_substr(&line[*i], 0, size);
	new_token = token_lstnew(str);
	*i += size;
	return (new_token);
}

t_token *lexer(char *line)
{
	int		i;
	t_token	*token_list;
	t_token	*new_token;

	if (!line)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		new_token = get_token(line, &i);
		if (new_token == NULL)
			break ;
		token_list = token_lstaddback(token_list, new_token);
	}
	return (token_list);
}
