/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:34:59 by sko               #+#    #+#             */
/*   Updated: 2019/10/30 16:35:01 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "ft_printf.h"

/*
** global dispatch checker structure
** c    : Display a single char (after conversion to unsigned int)
** s    : Display a string. The argument is a pointer to char.
** 		  Characters are displayed until a '\0' is encountered, or until the
**		  number of characters indicated by the precision have been displayed
** p    : The void * pointer argument is printed in hexadecimal
** 		  (as if by `%#x' or `%#lx')
** d, i : Display an int in signed decimal notation
** o    : Display an unsigned int in octal notation (without a leading 0)
** u, U : Display int in unsigned int decimal notation
** x    : lowercase Display an int in unsigned hexadecimal notation
** X    : uppercase Display an int in unsigned hexadecimal notation
** f, F : double or float (after conversion to double) in decimal notation
** Z    :
** %    : Display the % character
** 0    :
*/

t_dpt		g_dpt_checker[] =
{
	{'c', check_character},
	{'s', check_string}
};

/*
** need to modify change start with minimum filed width?
** @param fpf
** @param args
*/

void		flags_star_width(t_fpf *fpf, va_list args)
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

void		flags_star_precision(t_fpf *fpf, va_list args)
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

/*
** select specifier function
** @param str
** @param fpf
** @param args
** @return
*/

int			ft_select_specifier(const char *str, t_fpf *fpf, va_list args)
{
	int		i;
	int		len;
	char	*specifier;

	specifier = ft_strdup("cspdiouxXfFZU%0");
	flags_star_width(fpf, args);
	flags_star_precision(fpf, args);
	i = 0;
	len = 0;
	while (specifier[i] != '\0')
	{
		if (*str == specifier[i])
		{
			fpf->specifier = specifier[i];
			len = g_dpt_checker[i].ft(fpf, args);
			break ;
		}
		++i;
	}
	ft_strdel(&specifier);
	return (len);
}