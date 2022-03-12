/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:57:28 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/11 17:53:25 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "common.h"
#include "lexer.h"

static void
	free_token(t_token *token)
{
	free(token->str);
	free(token);
}

bool
	check_syntax_heredoc(t_token **args)
{
	t_token	*now;
	t_token	*p_2next;

	now = *args;
	while (now->next)
	{
		if (now->next->next)
			p_2next = now->next->next;
		if (now->type == D_LESSER && p_2next->type == WORD)
			return (FALSE);
		now = now->next;
	}
	return (TRUE);
}

void
	storeed_line(char *str, t_heredoc *hdoc)
{
	str = ft_strjoin(str, "\n");
	if (!str)
		error_exit(NULL);
	if (!(token_lstaddback(hdoc->contents,
				token_lstnew(ft_strdup(str)))))
		error_exit(NULL);
}

t_token
	*cut_heredoc_elem(t_token *args)
{
	t_token	*now;
	t_token	*p_2next;

	now = args;
	if (now->next)
		p_2next = now->next->next;
	else
		p_2next = NULL;
	if (p_2next && p_2next->type == WORD)
	{
		now->prev->next = p_2next;
		p_2next->prev = now->prev;
		free_token(now->next);
		free_token(now);
	}
	return (p_2next);
}

t_token
	*insert_heredoc(t_token *args, t_token *hdoc)
{
	t_token	*now;
	t_token	*p_2next;
	t_token	*hdoc_last;

	now = args;
	if (now->next)
		p_2next = now->next->next;
	else
		p_2next = NULL;
	now->prev->next = hdoc;
	hdoc_last = token_lstlast(hdoc);
	hdoc_last->next = p_2next;
	if (p_2next)
		p_2next->prev = hdoc_last;
	return (p_2next);
}
