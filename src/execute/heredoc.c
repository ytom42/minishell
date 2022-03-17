/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:12:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/17 22:05:38 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "lexer.h"
#include "expansion.h"

static bool
	need_hdoc_expansion(char *str)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		return (FALSE);
	return (TRUE);
}

// static void
// 	init_heredoc(t_heredoc **hdoc, t_redirect *redir)
// {
// 	t_redirect	*tmp;

// 	*hdoc = (t_heredoc *)malloc(sizeof(t_heredoc));
// 	if (!*hdoc)
// 		error_exit(NULL);
// 	(*hdoc)->contents = NULL;
// 	(*hdoc)->is_expand = FALSE;
// 	(*hdoc)->d_lesser = 0;
// 	(*hdoc)->eof_list = NULL;
// 	tmp = redir;
// 	while (tmp->next)
// 	{
// 		if (tmp->type == D_LESSER && tmp->next == WORD)
// 		{
// 			(*hdoc)->d_lesser++;
// 			if (!token_lstaddback((*hdoc)->eof_list, tmp->next))
// 				error_exit(NULL);
// 			if (need_hdoc_expansion(tmp->filename))
// 				(*hdoc)->is_expand = TRUE;
// 		}
// 		tmp = tmp->next;
// 	}
// }

static void
	save_heredoc(t_heredoc *hdoc, int d_lesser, bool is_valid_hdoc)
{
	char	*input_str;
	t_token	*eof_list;

	eof_list = hdoc->eof_list;
	input_str = NULL;
	while (42)
	{
		input_str = readline("> ");
		if (d_lesser > 2 && !ft_strcmp(input_str, eof_list->str)
			&& d_lesser--)
			eof_list = eof_list->next;
		else if (d_lesser == 1)
		{
			if (!ft_strcmp(input_str, eof_list->str))
				break ;
			if (is_valid_hdoc)
				storeed_line(input_str, hdoc);
		}
		input_str = NULL;
	}
}

static void
	convert_heredoc_cmd_arg(t_token **args, t_token *heredoc,
				 bool is_valid_hdoc, int d_lesser)
{
	t_token		*now;

	now = *args;
	while (now)
	{
		if (now->type == D_LESSER)
		{
			if (d_lesser != 1 || !is_valid_hdoc)
			{
				d_lesser--;
				now = cut_heredoc_elem(now);
				continue ;
			}
			else if (d_lesser == 1 && is_valid_hdoc)
			{
				now = insert_heredoc(now, heredoc);
				break ;
			}
		}
		now = now->next;
	}
}

void
	set_heredoc(t_command *cmd)
{
	t_redirect	*redir;
	bool		is_valid_hdoc;
	int			d_lesser;
	t_heredoc	*heredoc;

	redir = cmd->redirects;
	heredoc = redir->heredoc;
	is_valid_hdoc = check_syntax_heredoc(&cmd->args);
	// init_heredoc(&heredoc, redir);
	d_lesser = heredoc->d_lesser;
	save_heredoc(heredoc, d_lesser, is_valid_hdoc);
	if (is_valid_hdoc && heredoc->is_expand)
		expand_tokens(&heredoc->contents);
	convert_heredoc_cmd_arg(&cmd->args, heredoc->contents,
		is_valid_hdoc, d_lesser);
	del_heredoc(heredoc);
}
