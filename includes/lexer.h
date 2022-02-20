/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:33:43 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/02/20 16:01:14 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "common.h"

/*
**	lexer
*/
char		*get_line();
t_token		*lexer(char *line);

/*
**	lexer_lst
*/
t_token		*token_lstnew(char *str);
t_token		*token_lstlast(t_token *lst);
t_token		*token_lstaddback(t_token *lst, t_token *new);
void		token_lstclear(t_token *lst);

/*
**	lexer_utils
*/
int		is_delimiter(char c);
int		is_space(char c);
void	skip_space(char *line, int *i);

/*
**	debug
*/
void		print_token(t_token *lst);


#endif
