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

#define IS_SPACIFIER(x) (x == 'c' || x == 's' || x == 'd' || x == 'i' ||\
		x == 'p' || x == 'o' || x == 'u' || x == 'x' ||\
		x == 'X' || x == 'f' || x == 'Z' || x == 'U' || x == '%')

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
	{'s', check_string},
	{'d', check_integer},
	{'i', check_integer},
	{'o', check_oct_hex},
	{'x', check_oct_hex},
	{'X', check_oct_hex},
	{'p', check_pointer},
	{'f', check_float},
	{'F', check_float},
	{'u', check_unsigned_dec_int},
	{'U', check_unsigned_dec_int},
	{'Z', check_z_percent},
	{'%', check_z_percent},
	{'0', NULL},
};

int64_t			signed_modifier(t_fpf *fpf, va_list args)
{
	int64_t	i = 0;

	if ((fpf->flags & TYPE_L || fpf->flags & TYPE_LL) && \
		(fpf->flags & SIXUP || fpf->flags & SIXDOWN || fpf->flags & EIGHT))
		fpf->flags |= TYPE_J;
	if ((fpf->flags & SMALLU && fpf->flags & TYPE_LL) \
		|| (fpf->flags & UNLONG && fpf->flags & TYPE_LL))
		return (va_arg(args, unsigned long long));
	else if (fpf->flags & TYPE_L)
		return (va_arg(args, long));
	else if (fpf->flags & TYPE_LL)
		return (va_arg(args, long long));
	else if (fpf->flags & TYPE_Z)
		return (va_arg(args, size_t));
	else if (fpf->flags & TYPE_CL)
		return (va_arg(args, long double));
	else if (fpf->flags & TYPE_J || fpf->flags & UNLONG)
		return (va_arg(args, unsigned long));
	else
		i = va_arg(args, int);
	if (fpf->flags & TYPE_H)
		i = (short)i;
	else if (fpf->flags & TYPE_HH)
		i = (char)i;
	return (i);
}


int			check_specifiers(const char *str, t_fpf *fpf)
{
	if (*str == 'o')
		fpf->flags |= EIGHT;
	else if (*str == 'x')
		fpf->flags |= SIXDOWN;
	else if (*str == 'X')
		fpf->flags |= SIXUP;
	else if (*str == 'u')
		fpf->flags |= SMALLU;
	else if (*str == 'U')
		fpf->flags |= UNLONG;
	if (IS_SPACIFIER(*str))
		return (1);
	return (0);
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

	specifier = ft_strdup("csdioxXpfFuUZ%0");
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
