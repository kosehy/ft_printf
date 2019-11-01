/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:05:05 by sko               #+#    #+#             */
/*   Updated: 2019/09/21 23:31:49 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The stpncpy() and strncpy() functions copy at most len characters from src
** into dst. If src is less than len characters long, the remainder of dst is
** filled with `\0' characters. Otherwise, dst is not terminated.
*/

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}
