/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:38:27 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/26 15:48:04 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expansion.h"
#include "utils.h"
#include "libft.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

static int
	open_file(t_redirect *redir)
{
	char	*filename;

	filename = redir->filename->data;
	if (redir->type == REDIR_INPUT)
		return (open(filename, O_RDONLY));
	if (redir->type == REDIR_OUTPUT)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

static bool
	check_redirect(t_redirect *redir, char *org_filename)
{
	if (redir->filename == NULL || redir->filename->next)
	{
		print_error_msg("ambiguous redirect", org_filename);
		return (FALSE);
	}
	redir->fd_file = open_file(redir);
	if (redir->fd_file < 0)
	{
		print_error_msg(strerror(errno), redir->filename->data);
		return (FALSE);
	}
	return (TRUE);
}

void
	update_redirects(t_command *cmd)
{
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir && redir->next)
		redir = redir->next;
	while (redir)
	{
		if (redir->fd_file >= 0)
		{
			if (close(redir->fd_file) < 0)
				error_exit(NULL);
		}
		if (redir->fd_backup >= 0)
		{
			if (dup2(redir->fd_backup, redir->fd_io) < 0
				|| close(redir->fd_backup) < 0)
				error_exit(NULL);
		}
		redir = redir->next;
	}
}

bool
	set_redirects(t_command *cmd)
{
	t_redirect	*redir;
	char		*org_filename;

	redir = cmd->redirects;
	while (redir)
	{
		org_filename = ft_strdup(redir->filename->data);
		if (!org_filename)
			error_exit(NULL);
		// expand_token(&redir->filename);
		if (!check_redirect(redir, org_filename))
		{
			free_set((void **)&org_filename, NULL);
			update_redirects(cmd);
			return (FALSE);
		}
		free_set((void **)&org_filename, NULL);
		redir = redir->next;
	}
	return (TRUE);
}

bool
	dup_redirects(t_command *cmd, bool is_parent)
{
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (is_parent)
		{
			redir->fd_backup = dup(redir->fd_io);
			if (!redir->backup < 0)
			{
				print_fd_error(redir->fd_io);
				return (FALSE);
			}
		}
		else
		{
			if (dup2(redir->fd_file, redir->fd_io) < 0)
			{
				print_fd_error(redir->fd_io);
				return (FALSE);
			}
			redir = redir->next;
		}
	}
	return (TRUE);
}
