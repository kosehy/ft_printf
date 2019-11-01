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
** put digit (need to modify F_EXIST and function)
** @param fpf
** @param str
** @return
*/

int			put_digit(t_fpf *fpf, char *str)
{
	int		i;

	i = 0;
	if (fpf->flags & OX_ZERO)
	{
		ft_putchar(' ');
		return (1);
	}
	else if (!(fpf->flags & F_EXIST) && fpf->flags & PRECISION && \
			!fpf->precision && str[0] == '0' && str[1] == '\0')
	{
		if (!fpf->width)
			return (0);
		ft_putchar(' ');
		return (1);
	}
	else
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			++i;
		}
	}
	return (i);
}

/*
** check the character
** @param fpf
** @param args
** @return
*/

int			check_character(t_fpf *fpf, va_list args)
{
	unsigned char	c;
	int				i;

	i = 1;
	c = (unsigned char)va_arg(args, int);
	if (fpf->flags & FLAGS_MINUS)
	{
		ft_putchar(c);
		while (i++ < fpf->width)
			ft_putchar(' ');
	}
	else if (fpf->width)
	{
		while (i++ < fpf->width)
		{
			if (fpf->flags & FLAGS_ZERO)
				ft_putchar('0');
			else
				ft_putchar(' ');
		}
		ft_putchar(c);
	}
	else
		ft_putchar(c);
	return (fpf->width > 0 ? fpf->width : 1);
}

/*
** check string precision
** @param fpf
** @param str
** @return count
*/

int			precision_string(t_fpf *fpf, char *str)
{
	int		count;
	int		i;

	count = 0;
	i = fpf->precision;
	while (i != 0)
	{
		ft_putchar(str[count++]);
		--i;
	}
	return (count);
}

int			width_digit(t_fpf *fpf, int width)
{
	int		count;

	count = 0;
	if (!(fpf->flags & FLAGS_MINUS) && fpf->flags & FLAGS_ZERO)
	{
		while (width-- > 0)
		{
			ft_putchar('0');
			++count;
		}
	}
	else
	{
		while (width-- > 0)
		{
			ft_putchar(' ');
			++count;
		}
	}
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
	int		count;
	int		width;

	count = 0;
	if (fpf->precision < len && !(fpf->flags & PRECISION_ZERO) \
		&& (fpf->flags & PRECISION) && *str)
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

/*
** consider if string has no precision
** @param fpf
** @param str
** @param len
** @return count
*/

int			normal_string(t_fpf *fpf, char *str, int len)
{
	int		count;
	int		width;
	int		prec;
	int		temp;

	prec = (!(fpf->flags & PRECISION_ZERO) && fpf->flags & PRECISION \
		? fpf->precision : len);
	count = 0;
	if (prec < len)
		temp = prec;
	else
		temp = len;
	temp = !*str ? 0 : temp;
	width = fpf->width - temp;
	count += width_digit(fpf, width);
	if (prec < len && *str)
		count += precision_string(fpf, str);
	else if (*str)
		count += put_digit(fpf, str);
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

	count = 0;
	str = va_arg(args, char*);
	if (str == NULL)
		str = "(null)";
	len = 0;
	while (str[len])
		++len;
	if (fpf->flags & FLAGS_MINUS)
		count = minus_string(fpf, str, len);
	else
		count = normal_string(fpf, str, len);
	return (count);
}
