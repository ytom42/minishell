/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:10:25 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/18 10:20:16 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <analyzer.h>

int
	check_syntax(t_token *head)
{
	t_token	*token;

	token = head;
	// パイプから始まっていたらエラー
	if (is_type_pipe(token))
		return (err_msg("Error: Starting with '|'"));
	while (token)
	{
		// クオートがあれば閉じているかチェック
		if (check_close_quote(token))
			return (err_msg("Error: Not closing quote"));
		// token->nextがなければbreak
		if (token->next)
			break ;
		// 有効なトークンかチェック
		// if (check_token_pair(token))
		// 	return (err_msg(""))
		token = token->next;
	}
	// リダイレクト、パイプで終わっているとエラー
	if (is_type_pipe(token) || is_type_redirect(token))
		return (err_msg("Error: Cannot end with pipe or redirect"));
	return (MS_SUCCUSE);
}

int
	request_process(t_master *master, char *line)
{
	bool	debug;

	debug = true;
	// トークンに区切る
	if (tokenize(&(master->tokens), line))
		return (MS_FALSE);
	// // 構文チェック
	// if (check_syntax(master->tokens))
	// 	return (MS_FALSE);
	// デバッグ（line, トークンリストの表示）
	if (debug)
	{
		print_line(line);
		print_tokens(master->tokens);
	}
	// 有効なコマンドに区切り、リストの作成
	// プロセスの実行
	return (MS_SUCCUSE);
}
