/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:53:54 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 13:49:55 by kfumiya          ###   ########.fr       */
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
	if (hdoc)
	{
		if (pipe(redir->heredoc->hdoc_pipe) < 0)
			error_exit(NULL);
	}
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
		close(hdoc->hdoc_pipe[0]);
		start = hdoc->contents;
		while (hdoc->contents)
		{
			write(hdoc->hdoc_pipe[1], hdoc->contents->str, \
					ft_strlen(hdoc->contents->str));
			hdoc->contents = hdoc->contents->next;
		}
		close(hdoc->hdoc_pipe[1]);
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
