/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:21:31 by sko               #+#    #+#             */
/*   Updated: 2019/09/19 21:23:56 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memchr() function locates the first occurrence of c (converted
** to an unsigned char) in string s. The memchr() function returns a
** pointer to the byte located, or NULL if no such byte exists within n bytes.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char*)s;
	while (++i <= n)
		if (*(ptr++) == (unsigned char)c)
			return ((void*)--ptr);
	return (0);
}
