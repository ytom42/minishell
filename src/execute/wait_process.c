/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:16:57 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/22 15:28:52 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "utils.h"
#include "libft.h"

extern t_master	g_master;

static void
	update_exit_cd(int wstatus, bool receve_sigint)
{
	int	signal;

	if (WIFEXITED(wstatus))
		g_master.exit_cd = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		signal = WTERMSIG(wstatus);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDOUT_FILENO);
		g_master.exit_cd = signal + 128;
	}
	if (receve_sigint)
		ft_putendl_fd("", STDOUT_FILENO);
}

void
	wait_process(t_command *cmd)
{
	int		wait_status;
	bool	has_child;
	bool	receve_sigint;

	has_child = FALSE;
	receve_sigint = FALSE;
	while (cmd)
	{
		if (cmd->pid != -1)
		{
			if (waitpid(cmd->pid, &wait_status, 0) < 0)
				error_exit(NULL);
			if (WIFSIGNALED(wait_status) && WTERMSIG(wait_status) == SIGINT)
				receve_sigint = TRUE;
			has_child = TRUE;
		}
		cmd = cmd->next;
	}
	if (!has_child)
		return ;
	update_exit_cd(wait_status, receve_sigint);
}
