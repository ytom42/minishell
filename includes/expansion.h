/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:30:28 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/27 14:40:32 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef enum	e_tokentype{
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
	D_GREATER = -3,
	// fd
	IO_NUMBER = -2,
	TOKEN = -1,
}				t_token_type;

typedef enum	e_token_state{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
}				t_token_state;


typedef struct s_expander
{
	size_t	index;
	t_token_state state;
	t_token_type type;
	char *str;
} t_expander;

t_token_type get_token_type(char c);
t_token_state get_token_state(t_token_state state, t_token_type type);
void expand_tokens(t_token **tokens);
char *expand_env_var(char *str);
char **split_value(char *value, char delimiter);
void require_expansion(t_command *cmd, char ***args);

#endif
