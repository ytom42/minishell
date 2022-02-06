/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:47:40 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/10 05:06:48 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <analyzer.h>

void
	destory_token_list(char **token_types)
{
	int	i;

	i = -1;
	while (++i < TYPE_STR)
		free(token_types[i]);
}

void
	make_token_list(char **token_types)
{
	token_types[TYPE_R_RDRCT] = ft_strdup(">");
	token_types[TYPE_RR_RDRCT] = ft_strdup(">>");
	token_types[TYPE_L_RDRCT] = ft_strdup("<");
	token_types[TYPE_LL_RDRCT] = ft_strdup("<<");
	token_types[TYPE_PIPE] = ft_strdup("|");
}

int
	get_token_type(char *token)
{
	int		token_type;
	char	**token_list;

	token_list = NULL;
	// トークンタイプを識別するための文字列リストの作成
	make_token_list(token_list);
	token_type = -1;
	while (token_type < TYPE_STR)
		if (!ft_strcmp(token, token_list[token_type]))
			break ;
	// トークンタイプを識別するための文字列リストの削除
	destory_token_list(token_list);
	// if (token_type == TYPE_STR)
	// 	while (*token && token_type != TYPE_EXPDBL)
	// 		if (is_quote(*token) || *token++ == DLL)
	// 			token_type = TYPE_EXPDBL;
	return (token_type);
}

t_token
	*new_token(char *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = token;
	new->type = get_token_type(token);
	new->next = NULL;
	return (new);
}

int
	append_token(t_token **head, t_token *new)
{
	t_token	*token;

	if (!head || !new)
		return (MS_FALSE);
	if (!*head)
	{
		*head = new;
		return (MS_SUCCUSE);
	}
	token = *head;
	while (token && token->next)
		token = token->next;
	token->next = new;
	return (MS_SUCCUSE);
}
