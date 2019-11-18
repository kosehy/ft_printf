/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_letter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:17:56 by sko               #+#    #+#             */
/*   Updated: 2019/10/30 12:17:57 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** consider if string has no precision
** @param fpf
** @param str
** @param len
** @return count
*/

int			normal_string(t_fpf *fpf, char *str, int len)
{
	int		ig_prec;
	int		tmp;
	int		count;
	int		prec;
	int		width;

	ig_prec = fpf->flags & IGNORE_PRECISION;
	count = 0;
	if (!ig_prec && fpf->flags & PRECISION)
		prec = fpf->precision;
	else
		prec = len;
	if (prec < len)
		tmp = prec;
	else
		tmp = len;
	if (!*str)
		tmp = 0;
	width = fpf->width - tmp;
	count += width_digit(fpf, width);
	if (prec < len && *str != '\0')
		count += precision_string(fpf, str);
	else if (*str != '\0')
		count += put_digit(fpf, str);
	return (count);
}

/*
** consider if string has minus precision
** @param fpf
** @param str
** @param len
** @return count
*/

int			minus_string(t_fpf *fpf, char *str, int len)
{
	int		ig_prec;
	int		prec;
	int		width;
	int		count;

	count = 0;
	ig_prec = fpf->flags & IGNORE_PRECISION;
	prec = fpf->flags & PRECISION;
	if (fpf->precision < len && !ig_prec && prec && *str != '\0')
		count += precision_string(fpf, str);
	else if (*str)
		count += put_digit(fpf, str);
	if (fpf->width > count)
	{
		width = fpf->width - count;
		count += width_digit(fpf, width);
	}
	return (count);
}

int			check_str_count(t_fpf *fpf, char *str, int len)
{
	int		minus_flag;
	int		count;

	count = 0;
	minus_flag = fpf->flags & FLAGS_MINUS;
	if (minus_flag)
		count = minus_string(fpf, str, len);
	else
		count = normal_string(fpf, str, len);
	return (count);
}

/*
** check the string
** @param fpf
** @param args
** @return count
*/

int			check_string(t_fpf *fpf, va_list args)
{
	char	*str;
	int		len;
	int		count;

	str = va_arg(args, char*);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	count = check_str_count(fpf, str, len);
	return (count);
}
