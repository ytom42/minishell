/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 06:27:13 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/10 14:47:33 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYZER_H
# define ANALYZER_H

# include "common.h"
# include "utils.h"

/*
 *************
 ** analyzer **
 *************
 */
/* 
	debug.c
*/
void					print_line(char *line);
void					print_tokens(t_token *head);
void					print_env(t_environ *head);

/* 
	create_token.c
*/
t_token					*new_token(char *token);
int						append_token(t_token **head, t_token *new);
int						get_token_type(char *token);
void					make_token_list(char **token_types);
void					destory_token_list(char **token_types);

/* 
	request.c
*/
int						request_process(t_master *master, char *line);
int						check_syntax(t_token *head);

/* 
	token.c
*/
int						tokenize(t_token **head, char *line);
int						get_token(t_token **head, char *line);
int						get_delimiter(t_token **head, char *line);

/* 
	an_utils1.c
*/
void					skip_white(char *line);
bool					is_white(int c);
bool					is_delimiter(int c);
bool					is_quote(char c);
bool					search_close_quote(char *line, int *i);

/* 
	an_utils2.c
*/
bool					is_double_redirect(char *line);
bool					is_redirect(char c);
bool					is_type_pipe(t_token *token);
bool					check_close_quote(t_token *token);
bool					is_type_redirect(t_token *token);

/* 
	an_utils3.c
*/


#endif
