/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 05:29:18 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/18 10:25:16 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <analyzer.h>

int
	get_delimiter(t_token **head, char **line)
{
	int	i;

	// 先頭の空白文字のスキップ
	skip_white(*line);
	// エラー処理（先頭文字がない、デリミタ文字の場合）
	if (!**line || !is_delimiter(**line))
		return (MS_FALSE);
	i = 1;
	// <<, >> の場合
	if (is_double_redirect(*line))
		i++;
	// トークンリストに追加
	if (append_token(head, new_token(ft_strndup(*line, i))))
		return (MS_FALSE);
	*line += i;
	return (MS_SUCCUSE);
}

int
	get_token(t_token **head, char **line)
{
	int	i;

	// 先頭の空白文字のスキップ
	skip_white(*line);
	i = -1;
	// 文字があり、デリミタ文字じゃない場合
	while ((*line)[++i] && !is_delimiter((*line)[i]))
		// クオートだった場合、閉じクオートがあるか探す
		if (is_quote((*line)[i]) && !search_close_quote(*line, &i))
			return (MS_FALSE);
	// トークンリストの作成
	if (i > 0)
		if (append_token(head, new_token(ft_strndup(*line, i))))
			return (MS_FALSE);
	*line += i;
	return (MS_SUCCUSE);
}

int
	tokenize(t_token **head, char *line)
{
	int	flg;

	flg = 0;
	while (*line && !flg)
	{
		// lineをトークンに区切る
		flg = get_token(head, &line);
		// デリミタがあった場合はデリミタを区切りリストに追加
		if (!flg)
			flg = get_delimiter(head, &line);
		else
			return (MS_FALSE);
	}
	if (flg)
		return (MS_FALSE);
	return (MS_SUCCUSE);
}
