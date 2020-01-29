/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 11:35:57 by priviere    ###    #+. /#+    ###.fr     */
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
	if (src[i] == '%')
	{
		par->type = '%';
		ret += my_printf_perc(par);
		if (src[i + 1] && src[i + 1] == '%')
			i++;
	}
	return (ret);
}

int		check_and_treat(va_list ml, t_params *par, const char *s, int i)
{
	int ret;

	ret = 0;
	ret += treat_flag(s, i, ml, par);
	if ((s[i] != '%' && (s[i] != 's' && s[i] != 'c' && s[i] != 'd' && s[i] != 'i' && s[i] != 'u' && s[i] != 'x' && s[i] != 'X' && s[i] != 'p')))
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
			ret += check_and_treat(my_list, par, s, i);
		}
		else if (s[i] != 0 && s[i] != '%')
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

//     ret = ft_printf("[%--*d]\n", -42, -42);
// 	printf("Retour de mon printf :%d\n", ret);
//     ret_printf = printf("[%--*d]\n", -42, -42);
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
