/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:53:54 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/28 00:08:57 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

#define READ	0
#define WRITE	1

void
	create_heredoc_pipe(t_redirect *redir)
{
	t_heredoc	*hdoc;

	hdoc = get_hdoc(redir);
	if (hdoc && pipe(hdoc->hdoc_pipe) < 0)
		error_exit(NULL);
}

void
	write_heredoc(t_redirect *redir)
{
	t_heredoc	*hdoc;
	t_token		*start;

	start = NULL;
	hdoc = get_hdoc(redir);
	if (hdoc)
	{
		start = hdoc->contents;
		close(hdoc->hdoc_pipe[READ]);
		while (hdoc->contents)
		{
			write(hdoc->hdoc_pipe[WRITE], hdoc->contents->str, \
					ft_strlen(hdoc->contents->str));
			hdoc->contents = hdoc->contents->next;
		}
		hdoc->contents = start;
	}
}

void
	set_hdoc_pipe(int hdoc_pipe[])
{
	if (close(hdoc_pipe[WRITE]) < 0
		|| dup2(hdoc_pipe[READ], STDIN_FILENO) < 0
		|| close(hdoc_pipe[READ]) < 0)
		error_exit(NULL);
}

void
	add_heredoc(t_command *cmd, t_heredoc *hdoc)
{
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir->next)
		redir = redir->next;
	while (redir)
	{
		if (redir->type == D_LESSER)
		{
			redir->heredoc = hdoc;
			break ;
		}
		redir = redir->prev;
	}
}
