/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:56:03 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/03 11:42:42 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "execute.h"
#include "libft.h"
#include "utils.h"

void
	print_filename_error(char *msg, char *cmd, char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (file)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void
	print_fd_error(int fd)
{
	char	*str_fd;

	if (fd < 0)
		print_error_msg(strerror(errno), "file descriptor out of range");
	else
	{
		str_fd = ft_itoa(fd);
		if (!str_fd)
			error_exit(NULL);
		print_error_msg(strerror(errno), str_fd);
		free_set((void **)&str_fd, NULL);
	}
}

void
	exit_execve_error(char *path)
{
	int	exit_cd;

	if (errno == ENOENT)
		exit_cd = CMD_NOT_FND;
	else
		exit_cd = CMD_NOT_EXEC;
	if (is_directory(path))
	{
		print_error_msg("is a directory", path);
		exit(exit_cd);
	}
	if (errno == ENOEXEC && !is_executable(path))
		errno = EACCES;
	print_error_msg(strerror(errno), path);
	exit(exit_cd);
}
