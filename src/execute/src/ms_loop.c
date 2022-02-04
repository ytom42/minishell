/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 21:37:50 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/11 16:39:22 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

void
	ms_loop(t_master *master)
{
	char	*line;
	bool	flg;

	flg = false;
	while (!flg)
	{
		line = readline(MS_PROMPT);
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		flg = request_process(master, line);
		free(line);
	}
}
