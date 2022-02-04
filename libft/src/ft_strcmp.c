/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 00:14:12 by kfumiya           #+#    #+#             */
/*   Updated: 2021/11/28 07:19:45 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;

	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	while (*s1_tmp && *s2_tmp)
	{
		if (*s1_tmp == *s2_tmp)
		{
			s1_tmp++;
			s2_tmp++;
		}
		else
			return (*s1_tmp - *s2_tmp);
	}
	return (*s1_tmp - *s2_tmp);
}
