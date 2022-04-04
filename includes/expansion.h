/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:30:28 by kfumiya           #+#    #+#             */
/*   Updated: 2022/04/04 14:25:54 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "utils.h"

typedef enum e_tokentype
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_TAB = '\t',
	CHAR_NULL = 0,
	D_SEMICOLON = -4,
	IO_NUMBER = -2,
	TOKEN = -1,
}	t_token_type;

typedef enum e_token_state
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
}	t_token_state;

typedef struct s_expander
{
	size_t			index;
	t_token_state	state;
	t_token_type	type;
	int				arg_index;
	char			*str;
}	t_expander;

/*
**	expand_rmquote.c
*/
void			remove_quote(t_token *token);
void			loop_token_rmquote(char *str, int state_dq, int state_sq);

/*
**	expand_str.c
*/
char			*create_value_str(char *str);

/*
**	expand_token.c
*/
void			expand_tokens(t_token **tokens, int is_heredoc);

/*
**	expand_utils_1.c
*/
char			**split_value(char *value, char delimiter);

/*
**	expand_utils_2.c
*/
t_token_type	get_token_type(char c);
t_token_state	get_token_state(t_token_state state, t_token_type type);
char			*close_dqoute_value(char *str);
void			expander_init(t_expander *exper, char *str, int index);

/*
**	expand_var.c
*/
char			*expand_env_var(char *str, int index, int is_heredoc);
char			*str_search_key(char *str);

/*
**	expand_filename.c
*/
bool			expand_filename(t_redirect *redir);

#endif
