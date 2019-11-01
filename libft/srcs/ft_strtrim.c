/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:41:36 by sko               #+#    #+#             */
/*   Updated: 2019/09/21 22:56:03 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a copy of the string
** given as argument without whitespaces at the beginning or at
** the end of the string. Will be considered as whitespaces the
** following characters ’ ’, ’\n’ and ’\t’. If s has no whitespaces
** at the beginning or at the end, the function returns a
** copy of s. If the allocation fails the function returns NULL.
*/

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(const char *s)
{
	const char			*result;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (*s == '\0')
		return (ft_strnew(0));
	result = s + ft_strlen(s) - 1;
	while (*result == ' ' || *result == '\t' || *result == '\n')
		result--;
	return (ft_strsub(s, 0, result - s + 1));
}
