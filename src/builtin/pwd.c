/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:53:50 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/17 17:11:14 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

extern t_master	g_master;

int
	exec_pwd(void)
{
	char *pwd;

	pwd = get_env_value("PWD");
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free_set((void **)&pwd, NULL);
	return (EXIT_SUCCESS);
}
