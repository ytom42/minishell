/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:53:54 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/25 17:06:05 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

#define READ	0
#define WRITE	1

void
	create_heredoc_pipe(t_redirect *redir, int hdoc_pipe[])
{
	while (redir)
	{
		if (redir->type == D_LESSER)
		{
			if (pipe(hdoc_pipe) < 0)
				error_exit(NULL);
			break ;
		}
		redir = redir->next;
	}
}

void
	write_heredoc(t_heredoc *hdoc, int hdoc_pipe[])
{
	if (hdoc)
	{
		close(hdoc_pipe[0]);
		while (hdoc->contents)
		{
			write(hdoc_pipe[1], hdoc->contents->str, \
					ft_strlen(hdoc->contents->str));
			hdoc->contents = hdoc->contents->next;
		}
		close(hdoc_pipe[1]);
	}
}

void
	set_hdoc_pipe(int hdoc_pipe[])
{
	if (close(hdoc_pipe[WRITE]) < 0 \
			|| dup2(hdoc_pipe[READ], STDIN_FILENO) < 0 \
			|| close(hdoc_pipe[READ]) < 0)
		error_exit(NULL);
}
