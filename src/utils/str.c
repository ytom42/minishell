/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:00:13 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/18 18:10:02 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_bool
	str_is_digit(char *str)
{
	size_t	i;
	t_bool	is_digit;

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
			break;
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
	size_t index;

	index = 0;
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (&(dest[index]));
}
