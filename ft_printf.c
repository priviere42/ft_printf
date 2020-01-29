/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 16:18:44 by priviere    ###    #+. /#+    ###.fr     */
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
		par->width = ft_atoi(&s[i]);
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
		par->width = ft_atoi(&s[i++]);
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
	if ((s[i] != '%' && (s[i] != 's' && s[i] != 'c' && s[i] != 'd' && s[i] != 'i' && s[i] != 'u' && s[i] != 'x' && s[i] != 'X' && s[i] != 'p')) || par->type == '%')
		ret += write(1, &s[i], 1);
	return (ret);
}

int		ft_printf(const char *s, ...)
{
	va_list		my_list;
	t_params	*par;
	int			i;
	int			ret;

	ret = 0;
	i = 0;
	va_start(my_list, s);
	while (s[i])
	{
		par = ft_init_par(par);
		if (s[i] != 0 && i != 0 && s[i - 1] == '%')
		{
			i = ft_check_flags(my_list, s, i, par);
			ret += treat_flag(s, i, my_list, par);
	//		printf("\npar->width = %d, par->flag = %c, par->precision = %d, par->type = %c, index = %i\n", par->width, par->flag, par->p, par->type, i);
			if (s[i] == '%')
			{
				par->type = '%';
				ret += my_printf_perc(par);
				if (s[i + 1] && s[i + 1] == '%')
					i++;
				if (s[i + 1] == 's' || s[i + 1] == 'c' || s[i + 1] == 'd' || s[i + 1] == 'i' || s[i + 1] == 'u' || s[i + 1] == 'p' || s[i + 1] == 'x' || s[i + 1] == 'X')
				{
					ret += write(1, &s[i + 1], 1);
					i++;
				}
			}
			if (par->type != '%')
				ret += check_and_treat(s, i, par);
		}
		else if ((s[i] != 0 && s[i] != '%') || par->type == '%')
			ret += write(1, &s[i], 1);
		i++;
		free(par);
	}
	return (ret);
}

// #include <limits.h>
// int main()
// {
//    // char *tutu = NULL;
// 	int ret = 0;
// 	int ret_printf = 0;

//     ret = ft_printf("%%%%p::[%010d]\n", -8473);
// 	printf("Retour de mon printf :%d\n", ret);
//     ret_printf = printf("%%%%p::[%010d]\n", -8473);
// 	printf("Retour du vrai printf :%d\n", ret_printf);
//     // ret = ft_printf("[%1.0d]\n", 10);
// 	// printf("Retour de mon printf :%d\n", ret);
//     // ret_printf = printf("[%1.0d]\n", 10);
// 	// printf("Retour du vrai printf :%d\n", ret_printf);
// 	return (0);
// }

// int main(void)
// {
//     int ret = 0, ret2 = 0;

//     ret = ft_printf("|%8.15d|\n", 42);
//     ret2 = dprintf(1, "|%8.15d|\n", 42);

//     if (ret != ret2)
//         dprintf(1, "ko in return\n");
//     return 0;
// }
