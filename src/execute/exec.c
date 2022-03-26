/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 11:35:49 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 21:29:44 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "utils.h"

extern t_master	g_master;

static void
	exec_pipeline(t_node *nodes)
{
	int				pipe[2];
	t_pipe_state	pipe_state;
	t_command		*cmd;

	pipe_state = PIPE_WRITE_ONLY;
	while (nodes->type == NODE_PIPE)
		nodes = nodes->left;
	cmd = nodes->command;
	while (cmd && !g_master.error_fork)
	{
		g_master.exit_cd = exec_command(cmd, &pipe_state, pipe);
		cmd = cmd->next;
	}
	if (g_master.error_fork)
		print_fork_error();
	wait_process(nodes->command);
}

static void
	exec_node(t_node *nodes)
{
	t_pipe_state	pipe_state;

	pipe_state = NO_PIPE;
	if (!nodes)
		return ;
	if (nodes->type == NODE_PIPE)
		exec_pipeline(nodes);
	else
	{
		g_master.exit_cd = exec_command(nodes->command, &pipe_state, NULL);
		wait_process(nodes->command);
	}
}

void
	exec_nodes(t_node *nodes)
{
	if (!nodes)
		return ;
	exec_node(nodes);
}
