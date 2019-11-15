/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:57:09 by sko               #+#    #+#             */
/*   Updated: 2019/10/17 22:32:50 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

# define FLAGS_MINUS		(1 << 1)
# define FLAGS_SPACE		(1 << 2)
# define FLAGS_PLUS			(1 << 3)
# define FLAGS_HASH			(1 << 4)
# define FLAGS_ZERO			(1 << 5)
# define WIDTH				(1 << 6)
# define PRECISION			(1 << 7)
# define TYPE_H				(1 << 8)
# define TYPE_HH			(1 << 9)
# define TYPE_Z				(1 << 10)
# define TYPE_L				(1 << 11)
# define TYPE_LL			(1 << 12)
# define TYPE_CL			(1 << 13)
# define TYPE_J				(1 << 14)
# define NUMBER_PRECISION	(1 << 15)
# define PRECISION_ZERO		(1 << 16)
# define IGNORE_PRECISION	(1 << 17)
# define OX_ZERO			(1 << 18)
# define FLOAT_EXIST		(1 << 19)
# define SIXUP				(1 << 20)
# define SIXDOWN			(1 << 21)
# define EIGHT				(1 << 22)
# define SMALLU				(1 << 23)
# define UNLONG				(1 << 24)
# define FLOAT_PLUS			(1 << 25)

/*
** dispatch table structure
*/

typedef struct	s_dispatch_t
{
	char	specifier;
	int		(*ft)();
}				t_dpt;

typedef struct	s_fpf
{
	int		flags;
	int		length;
	int		width;
	int		width_p;
	int		precision;
	int		prec_p;
}				t_fpf;

const char		*read_content(const char *str, t_fpf *fpf);
int				check_character(t_fpf *fpf, va_list args);

/*
** check_info.c
*/

const char		*ft_check_info(const char *str, t_fpf *fpf);

/*
** check_util.c
*/

int				check_flags(const char *str);
int				check_modifier(const char *str);
const char		*check_star(const char *str, t_fpf *fpf);
void			flags_star_width(t_fpf *fpf, va_list args);
void			flags_star_precision(t_fpf *fpf, va_list args);

/*
** check_util.c
*/

int				check_flags(const char *str);
const char		*check_star(const char *str, t_fpf *fpf);
void			flags_star_width(t_fpf *fpf, va_list args);
void			flags_star_precision(t_fpf *fpf, va_list args);

/*
** specifier.c
*/

int				check_specifiers(const char *str, t_fpf *fpf);
int64_t			signed_modifier(t_fpf *fpf, va_list args);
int				check_specifiers(const char *str, t_fpf *fpf);
int				ft_select_specifier(const char *str, t_fpf *fpf, va_list args);

/*
** util.c
*/

void			init_fpf(t_fpf *fpf);
int				is_digit(const char *str);
int				get_int64_len(int64_t nbr);
const char		*get_numbers(const char *str, t_fpf *fpf);
void			get_prec_numbers(t_fpf *fpf, int nbr);

/*
** uint_util.c
*/

int				base_len(int64_t nbr, int64_t base);
char			*ft_int64_itoa_base(int64_t value, int64_t base);
int				u_base_len(uint64_t nbr, uint64_t base);
char			*ft_uint64_itoa_base(uint64_t value, uint64_t base);

/*
** check_letter.c
*/

int				put_digit(t_fpf *fpf, char *str);
int				width_digit(t_fpf *fpf, int width);
int				check_character(t_fpf *fpf, va_list args);
int				check_string(t_fpf *fpf, va_list args);

/*
** check_number.c
*/
int				minus_digit(int sign);
int				flag_space_digit(int sign);
int				flag_plus_digit(int sign);
char			*ft_int64_itoa_base(int64_t value, int64_t base);
char			*ft_uint64_itoa_base(uint64_t value, uint64_t base);
int				check_integer(t_fpf *fpf, va_list args);

/*
** check_oct_hex.c
*/
int				check_oct_hex(t_fpf *fpf, va_list args);

/*
** check_pointer.c
*/
int				check_pointer(t_fpf *fpf, va_list args);

/*
** check_pointer.c
*/
int				check_float(t_fpf *fpf, va_list args);

/*
** check_pointer.c
*/
int				check_unsigned_dec_int(t_fpf *fpf, va_list args);

/*
** check_z_percent.c
*/
int				check_z_percent(t_fpf *fpf, va_list args);
#endif
