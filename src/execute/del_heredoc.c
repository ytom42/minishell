/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:10:28 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/11 16:12:57 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "execute.h"
#include "lexer.h"

void
	del_heredoc(t_heredoc *hdoc)
{
	token_lstclear(hdoc->contents);
	token_lstclear(hdoc->eof_list);
	free(hdoc);
}
