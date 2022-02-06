/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:27:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/04 19:41:50 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./common.h"
# include "../src/analyzer/includes/analyzer.h"
# include "../src/builtin/includes/builtin.h"
# include "../src/execute/includes/execute.h"
# include "../src/utils/includes/utils.h"

volatile sig_atomic_t	g_exit_status;

/*
	main.c
*/
int						init_master(int ac, char **av, t_master *master);
void					sigint_handler(int sig);


#endif
