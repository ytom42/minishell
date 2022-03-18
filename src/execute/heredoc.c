/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:12:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/18 13:33:08 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "lexer.h"
#include "expansion.h"

static void
	del_heredoc(t_heredoc **hdoc)
{
	token_lstclear((*hdoc)->contents);
	free(*hdoc);
}

static bool
	need_hdoc_expansion(char *str)
{
	if (ft_strchr(str, '\"'))
		return (TRUE);
	return (FALSE);
}

static void
	init_heredoc(t_heredoc **hdoc, t_redirect *redir)
{
	*hdoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!*hdoc)
		error_exit(NULL);
	(*hdoc)->contents = NULL;
	(*hdoc)->is_expand = FALSE;
	(*hdoc)->eof = redir->filename->str;
	if (need_hdoc_expansion((*hdoc)->eof))
		(*hdoc)->is_expand = TRUE;
}

static bool
	save_heredoc(t_heredoc **hdoc)
{
	char	*input_str;
	char	*eof;

	input_str = NULL;
	eof = (*hdoc)->eof;
	while (42)
	{
		input_str = readline("> ");
		if (!ft_strcmp(input_str, eof))
			break ;
		input_str = ft_strjoin(input_str, "\n");
		if (!input_str)
			error_exit(NULL);
		if (!(token_lstaddback((*hdoc)->contents,
				token_lstnew(ft_strdup(input_str)))))
			error_exit(NULL);
		input_str = NULL;
	}
	return (TRUE);
}

void
	set_heredoc(t_command *cmd)
{
	t_redirect	*redir;
	t_heredoc	*heredoc;
	bool		is_valid_hdoc;

	redir = cmd->redirects;
	heredoc = redir->heredoc;
	is_valid_hdoc = FALSE;
	while (redir)
	{
		if (redir->type == D_LESSER)
		{
			if (is_valid_hdoc)
				del_heredoc(&heredoc);
			init_heredoc(&heredoc, redir);
			is_valid_hdoc = save_heredoc(&heredoc);
			if (is_valid_hdoc && heredoc->is_expand)
				expand_tokens(&heredoc->contents);
		}
		redir = redir->next;
	}
}