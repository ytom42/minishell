/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:29:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/30 17:34:53 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expansion.h"

bool
	skip_redirect(t_redirect **redir, char *org_filename)
{
	*redir = (*redir)->next;
	free_set((void **)&org_filename, NULL);
	return (TRUE);
}
