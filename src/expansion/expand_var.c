/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:16:59 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/24 17:31:10 by ytomiyos         ###   ########.fr       */
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

void
	expander_init(t_expander *exper, char *str)
{
	exper->str = ft_strdup(str);
	if (exper->str == NULL)
		error_exit(NULL);
	exper->index = 0;
	exper->state = STATE_GENERAL;
}

static char
	*str_search_key(char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (*str == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(*str))
	{
		res = ft_strdup("");
		if (!res)
			error_exit(NULL);
	}
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
	char *value_str;
	char *tmp;
	char *res;

	value_str = create_value_str(value, exp->state, FALSE);
	if (!value_str)
		error_exit(NULL);
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
	call_value(t_expander *exp)
{
	char	*var_name;
	char	*value;
	char	*res;
	size_t	index_after_var;

	var_name = str_search_key(&exp->str[exp->index + 1]);
	if (!var_name)
		error_exit(NULL);
	if (!ft_strlen(var_name))
	{
		free_set((void **)&var_name, NULL);
		return ;
	}
	exp->str[exp->index] = '\0';
	index_after_var = exp->index + ft_strlen(var_name) + 1;
	value = get_env_value(var_name);
	res = swap_name_value(exp, value, index_after_var);
	if (!res)
		error_exit(NULL);
	free_set((void **)&var_name, NULL);
	free_set((void **)&value, NULL);
	free_set((void **)&(exp->str), NULL);
	exp->str = res;
}

char
	*expand_env_var(char *str)
{
	t_expander	exp;

	if (!str)
		return (NULL);
	expander_init(&exp, str);
	while (exp.str[exp.index])
	{
		exp.type = get_token_type(exp.str[exp.index]);
		exp.state = get_token_state(exp.state, exp.type);
		if (exp.type == CHAR_ESCAPE && !exp.str[exp.index + 1]
			&& ft_in_set(exp.str[exp.index + 1], "\\\'\"$"))
			exp.index++;
		else if ((exp.state == STATE_GENERAL || exp.state == STATE_IN_DQUOTE)
			&& exp.str[exp.index] == '$')
			call_value(&exp);
		exp.index++;
	}
	if (exp.state != STATE_GENERAL)
		g_master.error_flag = TRUE;
	return (exp.str);
}
