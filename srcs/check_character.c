/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_character.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:48:14 by sko               #+#    #+#             */
/*   Updated: 2019/11/16 11:48:24 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** check flag value in character
** @param fpf
*/

void			check_char_flag(t_fpf *fpf, unsigned char c, int i)
{
	if (fpf->flags & FLAGS_MINUS)
	{
		ft_putchar(c);
		while (i++ < fpf->width)
			ft_putchar(' ');
	}
	else if (fpf->width)
	{
		while (i < fpf->width)
		{
			++i;
			if (fpf->flags & FLAGS_ZERO)
				ft_putchar('0');
			else
				ft_putchar(' ');
		}
		ft_putchar(c);
	}
	else
		ft_putchar(c);
}

/*
** check the character
** @param fpf
** @param args
** @return
*/

int				check_character(t_fpf *fpf, va_list args)
{
	unsigned char	c;
	int				i;
	int				count;

	i = 1;
	c = (unsigned char)va_arg(args, int);
	check_char_flag(fpf, c, i);
	if (fpf->width > 0)
		count = fpf->width;
	else
		count = 1;
	return (count);
}
