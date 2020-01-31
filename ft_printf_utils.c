/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_utils.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 16:17:53 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 15:13:42 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check_wildcard(va_list my_list, const char *s, int i, t_params *par)
{
	int num;

	if (s[i] == '*')
	{
		if ((num = va_arg(my_list, int)) < 0)
		{
			par->w = -1 * num;
			par->flag = '-';
		}
		else
			par->w = num;
		i++;
	}
	if (s[i] == '.' && s[i + 1] == '*')
	{
		par->p = va_arg(my_list, int);
		if (par->p < 0)
			return (i + 2);
		i = i + 2;
	}
	return (i);
}

int		ft_check_flags(va_list my_list, const char *s, int i, t_params *par)
{
	if (s[i] == '0' || s[i] == '-')
	{
		par->flag = (s[i] == '0') && (s[i + 1] == '-') ? '-' : s[i];
		while (((s[i] == '0') && (s[i + 1] == '-'))
		|| ((s[i] == '-') && ((s[i + 1] == '0') || (s[i + 1] == '-'))))
			i++;
		i++;
	}
	if (s[i] >= '0' && s[i] <= '9')
	{
		par->w = ft_atoi(&s[i]);
		while (s[i] && (s[i] >= '0' && s[i] <= '9'))
			i++;
	}
	i = ft_check_wildcard(my_list, s, i, par);
	if ((s[i] == '.' && s[i + 1]))
		par->p = (s[i + 1] >= '0' && s[i + 1] <= '9') ? ft_atoi(&s[++i]) : -2;
	if (par->p == -2)
		return (++i);
	if ((par->flag != 'a') && s[i + 1] >= '0' && s[i + 1] <= '9'
	&& par->p == -1)
		par->w = ft_atoi(&s[i++]);
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
		i++;
	return (i);
}

int		treat_flag(const char *src, int i, va_list my_list, t_params *par)
{
	int ret;

	ret = 0;
	if (src[i] == 'd' || src[i] == 'i')
		ret += my_printf_nbr(my_list, par);
	if (src[i] == 's')
		ret += my_printf_str(my_list, par);
	if (src[i] == 'c')
		ret += my_printf_char(my_list, par);
	if (src[i] == 'u')
		ret += my_printf_unbr(my_list, par);
	if (src[i] == 'X')
		ret += my_printf_majhexa(my_list, par);
	if (src[i] == 'x')
		ret += my_printf_hexa(my_list, par);
	if (src[i] == 'p')
		ret += my_printf_p(my_list, par);
	return (ret);
}

int		check_and_treat(const char *s, int i, t_params *par)
{
	int ret;

	ret = 0;
	if ((s[i] != '%' && (s[i] != 's' && s[i] != 'c' &&
	s[i] != 'd' && s[i] != 'i' && s[i] != 'u' &&
	s[i] != 'x' && s[i] != 'X' && s[i] != 'p'))
	|| par->type == '%')
		ret += write(1, &s[i], 1);
	return (ret);
}

int		*my_fct(t_params *par, va_list my_list, const char *s, int *r)
{
	if (s[r[0]] != 0 && r[0] != 0 && s[r[0] - 1] == '%')
	{
		r[0] = ft_check_flags(my_list, s, r[0], par);
		r[1] += treat_flag(s, r[0], my_list, par);
		if (s[r[0]] == '%')
		{
			par->type = '%';
			r[1] += my_printf_perc(par);
			if (s[r[0] + 1] && s[r[0] + 1] == '%')
				r[0]++;
			if (s[r[0] + 1] == 's' || s[r[0] + 1] == 'c' || s[r[0] + 1] == 'd'
			|| s[r[0] + 1] == 'i' || s[r[0] + 1] == 'u' || s[r[0] + 1] == 'p'
			|| s[r[0] + 1] == 'x' || s[r[0] + 1] == 'X' || s[r[0] + 1] == '*')
			{
				r[1] += write(1, &s[r[0] + 1], 1);
				r[0]++;
			}
		}
		if (par->type != '%')
			r[1] += check_and_treat(s, r[0], par);
	}
	else if ((s[r[0]] != 0 && s[r[0]] != '%') || par->type == '%')
		r[1] += write(1, &s[r[0]], 1);
	return (r);
}
