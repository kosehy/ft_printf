/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:07:19 by sko               #+#    #+#             */
/*   Updated: 2019/09/19 21:09:05 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*ptr;
	char			*ptr2;

	if (dst == NULL && src == NULL)
		return (dst);
	ptr = dst;
	ptr2 = (char *)src;
	while (n-- > 0)
		*(ptr++) = *(ptr2++);
	return (dst);
}
