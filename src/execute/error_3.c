/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:00:56 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/26 20:56:07 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "utils.h"

extern t_master	g_master;

void
	print_fork_error(void)
{
	ft_putendl_fd("minishell: Resource temporarily unavailable", \
					STDERR_FILENO);
	g_master.exit_cd = 1;
	g_master.error_fork = TRUE;
}
