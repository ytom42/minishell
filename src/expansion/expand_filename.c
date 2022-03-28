/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:16:00 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/28 22:44:38 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expansion.h"

static void
	free_for_fname(char **var_name, char **value)
{
	free_set((void **)var_name, NULL);
	free_set((void **)value, NULL);
}

static bool
	check_value(char *str, int index)
{
	char	*var_name;
	char	*value;
	size_t	index_after_var;
	int		i;

	var_name = str_search_key(&str[index + 1]);
	if (!var_name)
		return (TRUE);
	if (!ft_strlen(var_name))
		return (free_set((void **)&var_name, NULL), TRUE);
	str[index] = '\0';
	index_after_var = index + ft_strlen(var_name) + 1;
	value = get_env_value(var_name);
	if (!value)
		return (free_set((void **)&var_name, NULL), TRUE);
	i = -1;
	while (value[++i])
		if (value[i] == ' ')
			return (free_for_fname(&var_name, &value), FALSE);
	free_for_fname(&var_name, &value);
	return (TRUE);
}

bool
	expand_filename(t_redirect *redir)
{
	char	*filename;
	int		i;
	bool	err_flag;

	err_flag = FALSE;
	filename = ft_strdup(redir->filename->str);
	i = -1;
	while (filename[++i])
	{
		if (filename[i] == '$' && filename[i + 1])
			if (!check_value(filename, i))
				err_flag = TRUE;
	}
	if (err_flag)
		print_error_msg("ambiguous redirect", filename);
	free_set((void **)&filename, NULL);
	return (err_flag);
}
