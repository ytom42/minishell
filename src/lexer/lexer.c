/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:48:00 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/19 19:59:11 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	free(token);
}

static void	*free_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_token(tmp);
	}
	return (NULL);
}

static int		gl_size(char *line, int *i)
{
	int		size;

	size = 1;
	if (line[*i] == '>' && line[*i + 1] == '>')
		size += 1;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		size += 1;
	return (size);
}

static int		quote_size(char *line, int *i)
{
	int	size;

	size = 0;
	while (line[*i + size])
	{
		if (is_delimiter(line[*i + size]))
			break ;
		size += 1;
	}
	return (size);
}

static int get_token_size(char *line, int *i)
{
	if (line[*i] == '>' || line[*i] == '<')
		return (gl_size(line, i));
	else if (line[*i] == '|')
		return (1);
	else
		return (quote_size(line, i));
}

static t_token	*get_token(char *line, int *i)
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

static int	check_invalid_token(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	if (token == NULL)
		return (FALSE);
	str = token->str;
	while (str[i])
	{
		if (str[i] == ';' || str[i] == '\\')
		{
			free_token(token);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
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
		if (!check_invalid_token(new_token))
			return (free_list(token_list));
		token_list = token_lstaddback(token_list, new_token);
	}
	return (token_list);
}
