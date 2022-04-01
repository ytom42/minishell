/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:37:13 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/31 20:06:29 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

#define READ	0
#define WRITE	1

static bool
	can_write(t_pipe_state p_state)
{
	if (p_state == PIPE_WRITE_ONLY || p_state == PIPE_READ_WRITE)
		return (TRUE);
	return (FALSE);
}

static bool
	can_read(t_pipe_state p_state)
{
	if (p_state == PIPE_READ_ONLY || p_state == PIPE_READ_WRITE)
		return (TRUE);
	return (FALSE);
}

void
	create_pipe(t_pipe_state p_state, int new_pipe[])
{
	if (can_write(p_state))
	{
		if (pipe(new_pipe) < 0)
			error_exit(NULL);
	}
}

int
	dup_pipe(t_pipe_state p_state, int old_pipe[], int new_pipe[])
{
	if (can_read(p_state))
	{
		if (close(old_pipe[WRITE]) < 0
			|| dup2(old_pipe[READ], STDIN_FILENO) < 0
			|| close(old_pipe[READ]) < 0)
			error_exit(NULL);
	}
	if (can_write(p_state))
	{
		if (close(new_pipe[READ]) < 0
			|| dup2(new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(new_pipe[WRITE]) < 0)
			error_exit(NULL);
	}
	return (0);
}

void
	update_pipe(t_pipe_state p_state, int old_pipe[], int new_pipe[])
{
	if (can_read(p_state))
	{
		if (close(old_pipe[READ]) < 0 || close(old_pipe[WRITE]) < 0)
			error_exit(NULL);
	}
	if (can_write(p_state))
	{
		old_pipe[READ] = new_pipe[READ];
		old_pipe[WRITE] = new_pipe[WRITE];
	}
}
