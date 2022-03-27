/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:57:13 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/27 22:19:30 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void
	update_hdoc_pipe(t_command *cmd)
{
	t_heredoc	*hdoc;

	hdoc = get_hdoc(cmd->redirects);
	if (hdoc)
	{
		close(hdoc->hdoc_pipe[0]);
		close(hdoc->hdoc_pipe[1]);
	}
}

t_heredoc
	*get_hdoc(t_redirect *redir)
{
	t_heredoc	*hdoc;

	hdoc = NULL;
	while (redir)
	{
		if (redir->type == D_LESSER)
			hdoc = redir->heredoc;
		redir = redir->next;
	}
	return (hdoc);
}

void
	update_pipe_state(t_command *cmd, t_pipe_state *p_state)
{
	if (*p_state == NO_PIPE)
		return ;
	if (cmd->next && cmd->next->next)
		*p_state = PIPE_READ_WRITE;
	else
		*p_state = PIPE_READ_ONLY;
}

void
	update_info(t_command *cmd, t_pipe_state *p_state, char **args)
{
	update_hdoc_pipe(cmd);
	update_redirects(cmd);
	update_pipe_state(cmd, p_state);
	instant_free(args);
}
