/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:32:04 by sko               #+#    #+#             */
/*   Updated: 2019/10/17 22:32:24 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** get widh numbers
** @param str
** @param fpf
** @return
*/

const char	*get_numbers(const char *str, t_fpf *fpf)
{
	int	nbr;

	nbr = 0;
	while (is_digit(str))
	{
		fpf->flags |= WIDTH;
		nbr = nbr * 10 + (*str - '0');
		++str;
	}
	if (nbr > fpf->width)
		fpf->width = nbr;
	return (str);
}

/*
** read the width value from str
** managed minimum filed width (*)
** @param str
** @param fpf
** @return
*/

void		get_prec_numbers(t_fpf *fpf, int nbr)
{
	if (!(fpf->flags & PRECISION_ZERO))
	{
		if (fpf->precision != 0)
		{
			if (fpf->precision > nbr)
				fpf->precision = nbr;
			else
				fpf->precision = fpf->precision;
		}
		else
			fpf->precision = nbr;
	}
}

/*
** check contents
** @param content
** @param fpf
** @param args
** @return count
*/

int			ft_check_content(const char *content, t_fpf *fpf, va_list args)
{
	int		count;

	count = 0;
	while (*content != '\0')
	{
		if (*content == '%')
		{
			content = ft_check_info(++content, fpf);
			if (!check_specifiers(content, fpf))
				break ;
			fpf->length += ft_select_specifier(content, fpf, args);
		}
		else if (*content == '{' && (count = assign_color(content)))
			content = content + count + 1;
		else
		{
			ft_putchar(*content);
			fpf->length++;
		}
		++content;
	}
	return (fpf->length);
}

/*
** parsing function
** @param format
** @param args
** @return count
*/

int			ft_parse(const char *format, va_list args)
{
	t_fpf	fpf;
	int		count;

	count = ft_check_content((char *)format, &fpf, args);
	va_end(args);
	return (count);
}

/*
** ft_printf function
** @param format
** @param ...
** @return count
*/

int			ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;

	va_start(args, format);
	count = ft_parse(format, args);
	return (count);
}