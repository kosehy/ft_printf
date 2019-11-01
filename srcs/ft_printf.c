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

int			check_flags(const char *str)
{
	if (*str == '-' || *str == ' ' || *str == '+' || *str == '#' || \
		*str == '0')
		return (1);
	return (0);
}

int			check_modifier(const char *str)
{
	if (*str == 'h' || *str == 'l' || *str == 'L' || *str == 'j' || \
		*str == 'z')
		return (1);
	return (0);
}

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

void		get_prec_numbers_reduce_two(t_fpf *fpf, int nbr)
{
	if (!(fpf->flags & PRECISION_ZERO))
	{
		if (fpf->precision != 0)
		{
			if (fpf->precision > nbr)
				fpf->precision = nbr;
		}
		else
			fpf->precision = nbr;
	}
}

const char	*get_prec_number_reduce_one(const char *str, t_fpf *fpf)
{
	if (*str == '*')
	{
		fpf->prec_p = 1;
		++str;
	}
	return (str);
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
			fpf->length += ft_select_specifier(content, fpf, args);
		}
		else
		{
			ft_putchar(*content);
			++fpf->length;
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

int			main(void)
{
//	ft_printf("%c12sad", 'b');
//	printf("\n");
//	ft_printf("%s ", "asdvas");
//	printf("\n");
//	ft_printf("%s ", "asdvas");
//	printf("\n");
//	ft_printf("%s", "abc");
//	printf("\n");
//	ft_printf("%s", "this is a string");
//	printf("\n");
//	ft_printf("%s ", "this is a string");
//	printf("\n");
//	ft_printf("%s  ", "this is a string");
//	printf("\n");
//	ft_printf("this is a %s", "string");
//	printf("\n");
//	ft_printf("%s is a string", "this");
//	printf("\n");
//	ft_printf("Line Feed %s", "\\n");
//	printf("\n");ft_printf("%c12sad", 'b');
//	printf("\n");
//	ft_printf("%s ", "asdvas");
//	printf("\n");
//	ft_printf("%s ", "asdvas");
//	printf("\n");
//	ft_printf("%s", "abc");
//	printf("\n");
//	ft_printf("%s", "this is a string");
//	printf("\n");
//	ft_printf("%s ", "this is a string");
//	printf("\n");
//	ft_printf("%s  ", "this is a string");
//	printf("\n");
//	ft_printf("this is a %s", "string");
//	printf("\n");
//	ft_printf("%s is a string", "this");
//	printf("\n");
//	ft_printf("Line Feed %s", "\\n");
//	printf("\n");
 	ft_printf("%10s is a string", "this");
	printf("\n");
//	ft_printf("%.2s is a string", "this");
//	printf("\n");
//	ft_printf("%5.2s is a string", "this");
//	printf("\n");
//	ft_printf("%10s is a string", "");
//	printf("\n");
//	ft_printf("%.2s is a string", "");
//	printf("\n");
//	ft_printf("%5.2s is a string", "");
//	printf("\n");
//	ft_printf("%-10s is a string", "this");
//	printf("\n");
//	ft_printf("%-.2s is a string", "this");
//	printf("\n");
//	ft_printf("%-5.2s is a string", "this");
//	printf("\n");
//	ft_printf("%-10s is a string", "");
//	printf("\n");
//	ft_printf("%-.2s is a string", "");
//	printf("\n");
//	ft_printf("%-5.2s is a string", "");
//	printf("\n");
//	ft_printf("%s %s", "this", "is");
//	printf("\n");
//	ft_printf("%s %s %s", "this", "is", "a");
//	printf("\n");
//	ft_printf("%s %s %s %s", "this", "is", "a", "multi");
//	printf("\n");
//	ft_printf("%s%s%s%s%s", "this", "is", "a", "multi", "string");
//	printf("\n");
//	ft_printf("@moulitest: %s", NULL);
//	printf("\n");
	return (0);
}

/*
** //	ft_printf("%5c", 'c');
** //	printf("\n");
** //	ft_printf("%-5c", 'c');
** //	printf("\n");
** //	ft_printf("@moulitest: %c", 0);
** //	printf("\n");
** //	ft_printf("%2c", 0);
*/
