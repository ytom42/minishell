/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 05:32:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/19 10:35:23 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

t_environ
	*new_env(char *key, char *value)
{
	t_environ	*new;

	new = malloc(sizeof(t_environ));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->is_env = 1;
	return (new);
}

int
	append_env(t_environ **head, t_environ *new)
{
	t_environ	*tmp;

	if (!head || !new)
	{
		printf("no\n");
		return (MS_FALSE);
	}
	printf("new: %s\n", new->key);
	if (!*head)
	{
		printf("ok\n");
		*head = new;
		printf("head->key: %s\n", (*head)->key);
		return (MS_SUCCUSE);
	}
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (MS_SUCCUSE);
}

int
	create_env(t_master *master)
{
	// 下記の記述で既存の環境変数リストの取得ができる
	extern char	**environ;
	char		**split;
	int			i;

	master->environ = (t_environ *)malloc(sizeof(t_environ));
	i = 0;
	// 環境変数のリストが存在した場合（初期状態では既存の環境変数リストが渡されるはず、、、）
	while (environ[i])
	{
		printf("environ: %s\n", environ[i]);
		// 既存環境変数は "TERM=xterm"の様な形で保存されている
		split = ft_split(environ[i], '=');
		if (!split || !split[0] || !split[1])
		{
			// printf("check\n");
			return (MS_FALSE);
		}
		// 自作の環境変数のリスト追加していく
		if (append_env(&(master->environ),
				new_env(strdup(split[0]), strdup(split[1]))))
		{
			// printf("check\n");
			instant_free(split);
			return (MS_FALSE);
		}
		// int j = 0;
		// while (split[j])
		// {
		// 	printf("split[%d]: %s\n", j, split[j]);
		// 	j++;
		// }
		instant_free(split);
		i++;
	}
	// // プリセット設定
	// if (preset_env(master))
	// {
	// 	// printf("check\n");
	// 	return (MS_FALSE);
	// }
	return (MS_SUCCUSE);
}
