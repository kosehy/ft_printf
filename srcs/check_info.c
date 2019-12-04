/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:26:11 by sko               #+#    #+#             */
/*   Updated: 2019/10/30 16:26:15 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "ft_printf.h"

const char	*set_flags(const char *str, t_fpf *fpf)
{
	while (check_flags(str))
	{
		if (*str == '-')
			fpf->flags |= FLAGS_MINUS;
		else if (*str == ' ')
			fpf->flags |= FLAGS_SPACE;
		else if (*str == '+')
			fpf->flags |= FLAGS_PLUS;
		else if (*str == '#')
			fpf->flags |= FLAGS_HASH;
		else if (*str == '0')
			fpf->flags |= FLAGS_ZERO;
		++str;
	}
	return (str);
}

const char	*set_modifiers(const char *str, t_fpf *fpf)
{
	while (check_modifiers(str))
	{
		if (*str == 'j' && *(str++))
			fpf->flags |= TYPE_J;
		else if (*str == 'h' && *(str + 1) == 'h' && \
				*(str++) && *(str++))
			fpf->flags |= TYPE_HH;
		else if (*str == 'h' && *(str++))
			fpf->flags |= TYPE_H;
		else if (*str == 'l' && *(str++))
			fpf->flags |= TYPE_L;
		else if (*str == 'l' && *(str + 1) == 'l' && \
				*str++ != '\0' && *str++)
			fpf->flags |= TYPE_LL;
		else if (*str == 'L' && *(str++))
			fpf->flags |= TYPE_CL;
		else if (*str == 'z' && *(str++))
			fpf->flags |= TYPE_Z;
	}
	return (str);
}

const char	*set_width(const char *str, t_fpf *fpf)
{
	if (*str == '*')
	{
		fpf->width_p = 1;
		++str;
	}
	if (*str == '-')
	{
		fpf->flags |= FLAGS_MINUS;
		++str;
	}
	str = get_numbers(str, fpf);
	if (*str == '*')
	{
		fpf->width_p = 1;
		++str;
	}
	return (str);
}

const char	*set_precision(const char *str, t_fpf *fpf)
{
	int	nbr;

	if (*str == '.')
	{
		fpf->flags |= PRECISION;
		++str;
		str = check_star(str, fpf);
		nbr = 0;
		while (is_digit(str))
		{
			fpf->flags |= NUMBER_PRECISION;
			nbr = nbr * 10 + (*str - '0');
			++str;
		}
		if ((!(fpf->flags & NUMBER_PRECISION) && !fpf->width_p) || \
			(fpf->flags & NUMBER_PRECISION && nbr == 0))
			fpf->flags |= PRECISION_ZERO;
		get_prec_numbers(fpf, nbr);
		str = check_star(str, fpf);
	}
	return (str);
}

const char	*ft_check_info(const char *str, t_fpf *fpf)
{
	char	*specifier;
	int		i;

	i = 0;
	init_fpf(fpf);
	specifier = ft_strdup(" -+#0jhlzL.*0123456789");
	while (specifier[i] != '\0')
	{
		if (*str == specifier[i])
		{
			str = set_flags(str, fpf);
			str = set_modifiers(str, fpf);
			str = set_width(str, fpf);
			str = set_precision(str, fpf);
			i = 0;
		}
		++i;
	}
	ft_strdel(&specifier);
	return (str);
}
