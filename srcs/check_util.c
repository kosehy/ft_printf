/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 21:19:07 by sko               #+#    #+#             */
/*   Updated: 2019/11/08 21:19:09 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "ft_printf.h"

/*
** check flags
** @param str
** @return
*/

int				check_flags(const char *str)
{
	if (*str == '-' || *str == ' ' || *str == '+' || *str == '#' || \
		*str == '0')
		return (1);
	return (0);
}

/*
** check flags
** @param str
** @return
*/

int				check_modifiers(const char *str)
{
	if (*str == 'h' || *str == 'l' || *str == 'L' || *str == 'j' || \
		*str == 'z')
		return (1);
	return (0);
}

/*
** check star
** @param str
** @param fpf
** @return
*/

const char		*check_star(const char *str, t_fpf *fpf)
{
	if (*str == '*')
	{
		fpf->prec_p = 1;
		++str;
	}
	return (str);
}

/*
** need to modify change start with minimum filed width?
** @param fpf
** @param args
*/

void			flags_star_width(t_fpf *fpf, va_list args)
{
	int		width;

	if (fpf->width_p)
	{
		width = va_arg(args, int);
		if (!(fpf->flags & WIDTH))
		{
			if (width < 0)
			{
				width *= -1;
				fpf->flags |= FLAGS_MINUS;
			}
			fpf->width = width;
		}
	}
}

/*
** need to modify change start with minimum filed width?
** @param fpf
** @param args
*/

void			flags_star_precision(t_fpf *fpf, va_list args)
{
	int		precision;

	if (fpf->prec_p)
	{
		precision = va_arg(args, int);
		if (!(fpf->flags & NUMBER_PRECISION))
		{
			if (precision < 0)
			{
				fpf->flags |= IGNORE_PRECISION;
				fpf->precision = 6;
			}
			else
				fpf->precision = precision;
		}
	}
}
