/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 22:50:42 by sko               #+#    #+#             */
/*   Updated: 2019/09/20 22:55:35 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	unsigned int	pos;
	unsigned int	i;

	if (!*to_find)
		return ((char*)str);
	pos = 0;
	while (str[pos] != '\0')
	{
		if (str[pos] == to_find[0])
		{
			i = 0;
			while (to_find[i] == '\0' || str[pos + i] == to_find[i])
			{
				++i;
				if (to_find[i] == '\0')
					return ((char*)&str[pos]);
			}
		}
		++pos;
	}
	return (0);
}
