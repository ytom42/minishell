/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:27:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/14 11:35:58 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./common.h"
# include "../src/analyzer/includes/analyzer.h"
# include "../src/builtin/includes/builtin.h"
# include "../src/execute/includes/execute.h"
# include "../src/utils/includes/utils.h"

/*
	main.c
*/
int						init_master(int ac, char **av, t_master *master);
void					sigint_handler(int sig);


#endif
