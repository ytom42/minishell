/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:16:16 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/10 05:52:35 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int
	preset_env_shlvl(t_master *master)
{
	t_environ	*tmp;
	int			lvl;
	char		*str_lvl;

	// 自作環境変数リストから"SHLVL"の検索
	tmp = search_key(master->environ, "SHLVL");
	// 既にある場合
	if (tmp)
	{
		// レベルを取得
		lvl = ft_atoi(tmp->value);
		// 1000以上の場合は１に設定
		if (lvl > 999)
			replace_env_value(tmp, "1");
		else
		{
			str_lvl = ft_itoa(lvl);
			replace_env_value(tmp, str_lvl);
			free(str_lvl);
		}
	}
	// 新規登録
	else
	{
		if (append_env(&(master->environ),
				new_env(ft_strdup("SHLVL"), ft_strdup("1"))))
			return (MS_FALSE);
	}
	return (MS_SUCCUSE);
}

int
	preset_env_pwd_oldpwd(t_master *master)
{
	t_environ	*target;

	// 自作環境変数リストで”PWD”の検索
	target = search_key(master->environ, "PWD");
	// 登録の分岐
	if (target)
		release_target(target);
	else if (append_env(&(master->environ), new_env("PWD", master->pwd)))
		return (MS_FALSE);
	// ”OLDPWD”の検索
	target = search_key(master->environ, "OLDPWD");
	// 既に追加されていたら
	if (target)
		release_target(target);
	else if (append_env(&(master->environ), new_env("OLDPWD", NULL)))
		return (MS_FALSE);
	return (MS_SUCCUSE);
}

int
	preset_env(t_master *master)
{
	// pwd, oldpwdのプリセット
	if (preset_env_pwd_oldpwd(master))
		return (MS_FALSE);
	// shelvlのプリセット
	if (preset_env_shlvl(master))
		return (MS_FALSE);
	return (MS_SUCCUSE);
}
