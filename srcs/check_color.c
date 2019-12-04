/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:28:00 by sko               #+#    #+#             */
/*   Updated: 2019/11/15 09:28:03 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ct			g_ct[] =
{
	{"red", "\x1B[31m"},
	{"green", "\x1B[32m"},
	{"blue", "\x1B[34m"},
	{"eoc", "\033[0m"},
	{NULL, NULL},
};

/*
** assign the color based on the string value
** @param str
** @return
*/

int				assign_color(const char *str)
{
	int		i;
	int		j;
	char	tmp[6];

	i = 0;
	j = 0;
	++str;
	while (str[i] != '}')
	{
		tmp[i] = str[i];
		++i;
	}
	tmp[i] = '\0';
	while (j < 4)
	{
		if (!(ft_strcmp(g_ct[j].color, tmp)))
		{
			ft_putstr(g_ct[j].result);
			return (i);
		}
		++j;
	}
	return (0);
}
