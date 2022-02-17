/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:27:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/15 18:04:44 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "common.h"
# include "analyzer.h"
# include "builtin.h"
# include "execute.h"
# include "utils.h"

volatile sig_atomic_t	g_exit_status;

/*
	main.c
*/
int						init_master(int ac, char **av, t_master *master);
void					sigint_handler(int sig);

#endif
