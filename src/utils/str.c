/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:00:13 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/27 12:18:12 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

static int
	ft_isspace(char c)
{
	if (ft_strchr(" \t\n\r\v\f", c))
		return (1);
	return (0);
}

bool
	str_is_digit(char *str)
{
	size_t	i;
	bool	is_digit;

	i = 0;
	is_digit = FALSE;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			is_digit = TRUE;
		else
			break ;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' && is_digit == TRUE)
		return (TRUE);
	return (FALSE);
}

char
	*ft_strcpy_forward(char *dest, char *src)
{
	size_t	index;

	index = 0;
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (&(dest[index]));
}

bool
	str_is_sign(char *str)
{
	size_t	i;
	bool	is_digit;

	i = 0;
	is_digit = FALSE;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		return (TRUE);
	return (FALSE);
}
