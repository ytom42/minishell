/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:53:50 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/24 14:31:43 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "libft.h"

extern t_master	g_master;

int
	exec_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free_set((void **)&pwd, NULL);
	return (EXIT_SUCCESS);
}
