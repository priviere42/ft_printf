/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 17:14:45 by priviere    ###    #+. /#+    ###.fr     */
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
			par->width = -1 * num;
			par->flag = '-';
		}
		else
			par->width = num;
		i++;
	}
	if (s[i] == '.' && s[i + 1] == '*')
	{
		par->precision = va_arg(my_list, int);
		if (par->precision < 0)
		{
			par->precision = -1 * par->precision;
			if (par->width == -1)
				par->flag = '-';
		}
		i = i + 2;
	}
	return (i);
}

int		ft_check_flags(va_list my_list, const char *src, int i, t_params *par)
{
	if (src[i] == '0' || src[i] == '-')
	{
		par->flag = (src[i] == '0') && (src[i + 1] == '-') ? '-' : src[i];
		if (((src[i] == '0') && (src[i + 1] == '-'))
		|| ((src[i] == '-') && (src[i + 1] == '0')))
			i++;
		i++;
	}
	if (src[i] >= '0' && src[i] <= '9')
	{
		par->width = ft_atoi(&src[i]);
		while (src[i] && (src[i] >= '0' && src[i] <= '9'))
			i++;
	}
	i = ft_check_wildcard(my_list, src, i, par);
	if ((src[i] == '.' && src[i + 1]))
		par->precision = ft_atoi(&src[++i]);
	if ((par->flag != 'a') && src[i + 1] >= '0' && src[i + 1] <= '9'
	&& par->precision == -1)
		par->width = ft_atoi(&src[i++]);
	while (src[i] && (src[i] >= '0' && src[i] <= '9'))
		i++;
//	printf("\npar->width = %d, par->flag = %c, par->precision = %d, index = %i\n", par->width, par->flag, par->precision, i);
	return (i);
}

int		ft_printf(const char *src, ...)
{
	va_list my_list;
	t_params *par;
	int i;
	int ret;

	ret = 0;
	va_start(my_list, src);
	i = 0;
	while (src[i])
	{
		par = ft_init_par(par);
		if (src[i] != 0 && i != 0 && src[i - 1] == '%')
		{
			i = ft_check_flags(my_list, src, i, par);
//			printf("\npar->width = %d, par->flag = %c, par->precision = %d, index = %d, src[i] = %c\n", par->width, par->flag, par->precision, i, src[i]);
			if (src[i] == 'd' || src[i] == 'i')
				ret += my_printf_nbr(my_list, par);
			if (src[i] == 's')
				ret += my_printf_str(my_list, par);
			if (src[i] == 'c')
				ret += my_printf_char(my_list, par);
			if (src[i] == '%')
			{
				par->type = '%';
				ret += my_printf_char(my_list, par);
			}
			if (src[i] == 'u')
				ret += my_printf_unbr(my_list, par);
			if (src[i] == 'X')
				ret += my_printf_majhexa(my_list, par);
			if (src[i] == 'x')
				ret += my_printf_hexa(my_list, par);
			if (src[i] == 'p')
				ret += my_printf_p(my_list, par);
			else if ((src[i] != '%' &&
			(src[i] != 's' && src[i] != 'c' && src[i] != 'd' && src[i] != 'i'
			&& src[i] != 'u' && src[i] != 'x' && src[i] != 'X')))
				ret += write(1, &src[i], 1);
		}
		else if (src[i] != '%')
			ret += write(1, &src[i], 1);
		i++;
		free(par);
	}
	return (ret);
}

// #include <limits.h>
// int main()
// {
// //	char* tutu = "sa";
// 	int ret = 0;
// 	int ret_printf = 0;

//     ret = ft_printf("ft_printf : |%6.0s|\n", NULL);
// 	printf("Retour de mon printf :%d\n", ret);
//     ret_printf = printf("printf    : |%6.0s|\n", NULL);
// 	printf("Retour du vrai printf :%d\n", ret_printf);
// 	return (0);
// }
