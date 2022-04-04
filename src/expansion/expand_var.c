/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:16:59 by kfumiya           #+#    #+#             */
/*   Updated: 2022/04/04 14:37:27 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execute.h"
#include "utils.h"

extern t_master	g_master;

#define KEY 0
#define VALUE 1
#define TMP 2
#define RES 3

static void
	instant_free_call(char **var_name, char **value, char **str)
{
	free_set((void **)var_name, NULL);
	free_set((void **)value, NULL);
	free_set((void **)str, NULL);
}

char
	*str_search_key(char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (*str == '?')
		return (ft_strdup("?"));
	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		error_exit(NULL);
	i = -1;
	while (++i < len)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

static char
	*swap_name_value(t_expander *exp, char *value, size_t after_var)
{
	char	*value_str;
	char	*tmp;
	char	*res;

	value_str = create_value_str(value);
	if (!value_str)
		return (NULL);
	tmp = ft_strjoin(exp->str, value);
	if (!tmp)
		error_exit(NULL);
	res = ft_strjoin(tmp, &exp->str[after_var]);
	if (!res)
		error_exit(NULL);
	exp->index = ft_strlen(tmp) - 1;
	free_set((void **)&value_str, NULL);
	free_set((void **)&tmp, NULL);
	return (res);
}

static void
	call_value(t_expander *exp, int is_heredoc)
{
	char	*var_name;
	char	*value;
	char	*res;
	size_t	index_after_var;

	var_name = str_search_key(&exp->str[exp->index + 1]);
	if (!var_name)
		return ;
	if (!ft_strlen(var_name))
	{
		free_set((void **)&var_name, NULL);
		return ;
	}
	exp->str[exp->index] = '\0';
	index_after_var = exp->index + ft_strlen(var_name) + 1;
	value = get_env_value(var_name);
	if (!value)
		value = ft_strdup("");
	else if (exp->arg_index > 0 && !is_heredoc)
		value = close_dqoute_value(value);
	res = swap_name_value(exp, value, index_after_var);
	instant_free_call(&var_name, &value, &(exp->str));
	exp->str = res;
}

char
	*expand_env_var(char *str, int index, int is_heredoc)
{
	t_expander	exp;

	if (!str)
		return (NULL);
	expander_init(&exp, str, index);
	if (!exp.str)
		return (NULL);
	while (exp.str[exp.index])
	{
		exp.type = get_token_type(exp.str[exp.index]);
		exp.state = get_token_state(exp.state, exp.type);
		if (exp.type == CHAR_ESCAPE && !exp.str[exp.index + 1]
			&& ft_in_set(exp.str[exp.index + 1], "\\\'\"$"))
			exp.index++;
		else if ((exp.state == STATE_GENERAL || exp.state == STATE_IN_DQUOTE)
			&& exp.str[exp.index] == '$')
			call_value(&exp, is_heredoc);
		exp.index++;
	}
	if (exp.state != STATE_GENERAL)
		g_master.error_flag = TRUE;
	free_set((void **)&str, NULL);
	return (exp.str);
}
