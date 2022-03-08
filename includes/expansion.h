/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:30:28 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/08 20:23:38 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

// # include "execute.h"
# include "utils.h"

typedef enum	e_token_state
{
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

char *create_value_str(char *str, t_token_state status, bool is_env);
char **split_value(char *value, char delimiter);
void expand_tokens(t_token **tokens);
t_token_type get_token_type(char c);
t_token_state get_token_state(t_token_state state, t_token_type type);
char *expand_env_var(char *str);


#endif
