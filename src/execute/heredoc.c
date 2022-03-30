/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:12:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/30 15:34:56 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "lexer.h"
#include "expansion.h"

extern t_master	g_master;

static void
	del_heredoc(t_heredoc **hdoc)
{
	del_token_list((*hdoc)->contents);
	free_set((void **)&(*hdoc)->eof, NULL);
	free_set((void **)&(*hdoc), NULL);
}

static bool
	need_hdoc_expansion(char *str)
{
	if (ft_strchr(str, '\''))
		return (FALSE);
	return (TRUE);
}

static void
	init_heredoc(t_heredoc **hdoc, t_redirect *redir)
{
	*hdoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!*hdoc)
		error_exit(NULL);
	(*hdoc)->contents = NULL;
	(*hdoc)->is_expand = FALSE;
	(*hdoc)->error_flag = FALSE;
	if (close_qoute_filename(redir->filename->str) != STATE_GENERAL)
		(*hdoc)->error_flag = TRUE;
	(*hdoc)->eof = ft_strdup(redir->filename->str);
	if (need_hdoc_expansion((*hdoc)->eof))
		(*hdoc)->is_expand = TRUE;
	loop_token_rmquote((*hdoc)->eof, 0, 0);
	(*hdoc)->hdoc_pipe[0] = -1;
	(*hdoc)->hdoc_pipe[1] = -1;
}

static bool
	save_heredoc(t_heredoc **hdoc)
{
	char	*input_str;
	char	*eof;
	char	*tmp;

	input_str = NULL;
	eof = (*hdoc)->eof;
	while (42)
	{
		input_str = readline("> ");
		if (!input_str || !ft_strcmp(input_str, eof))
			break ;
		tmp = input_str;
		input_str = ft_strjoin(input_str, "\n");
		free_set((void **)&tmp, NULL);
		if (!input_str)
			error_exit(NULL);
		(*hdoc)->contents = (token_lstaddback((*hdoc)->contents, \
								token_lstnew(ft_strdup(input_str))));
		free_set((void **)&input_str, NULL);
	}
	if (input_str)
		free_set((void **)&input_str, NULL);
	return (TRUE);
}

void
	set_heredoc(t_command *cmd)
{
	t_redirect	*redir;
	t_heredoc	*heredoc;
	bool		is_valid_hdoc;

	redir = cmd->redirects;
	heredoc = NULL;
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
				expand_tokens(&heredoc->contents, TRUE);
		}
		redir = redir->next;
	}
	g_master.error_flag = FALSE;
	add_heredoc(cmd, heredoc);
}
