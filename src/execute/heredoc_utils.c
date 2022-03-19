/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:53:54 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/19 20:35:15 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void
	create_heredoc_pipe(t_redirect *redir, int hdoc_pipe[])
{
	while (redir)
	{
		if (redir->type == D_LESSER)
		{
			if (pipe(hdoc_pipe) < 0)
				error_exit(NULL);
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
			write(hdoc_pipe[1], hdoc->contents->str,
					ft_strlen(hdoc->contents->str));
			write(hdoc_pipe[1], "\n", 1);
			hdoc->contents = hdoc->contents->next;
		}
	}
}
