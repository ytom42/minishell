/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:33:43 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/03/26 19:04:38 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "common.h"

/*
**	lexer
*/
char		*get_line(void);
t_token		*lexer(char *line);

/*
**	lexer_token
*/
t_token		*get_token(char *line, int *i);

/*
**	lexer_lst
*/
t_token		*token_lstnew(char *str);
t_token		*token_lstlast(t_token *lst);
t_token		*token_lstaddback(t_token *lst, t_token *new);

/*
**	lexer_utils
*/
int			is_delimiter(char c);
int			is_space(char c);
void		skip_space(char *line, int *i);

#endif
