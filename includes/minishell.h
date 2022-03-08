/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:27:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/08 20:57:39 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "builtin.h"
# include "execute.h"
# include "expansion.h"
# include "utils.h"

volatile sig_atomic_t	g_exit_status;

/*
	main.c
*/
int						init_master(int ac, char **av, t_master *master);
void					sigint_handler(int sig);

#endif
