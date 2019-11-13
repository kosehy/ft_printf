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
