/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_nbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:37:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 10:38:29 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int my_printf_unbr(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base(num, 10));
	i = nbr_len - 1;
	{
		while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
		{
			ret += write(1, " ", 1);
			nbr_len++;
		}
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base(num, 10), ft_strlen(ft_ulltoa_base(num, 10)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int my_printf_nbr(va_list my_list, t_params *par)
{
    int num = va_arg(my_list, int);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_itoa_base(num, 10));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_itoa_base(num, 10), ft_strlen(ft_itoa_base(num, 10)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int	my_printf_hexa(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base(num, 16));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base(num, 16), ft_strlen(ft_ulltoa_base(num, 16)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int	my_printf_majhexa(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base_maj(num, 16));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base_maj(num, 16), ft_strlen(ft_ulltoa_base_maj(num, 16)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int		my_printf_p(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base(num, 16));
	i = nbr_len - 1;
//	printf("\npar->width = %d, par->flag = %c, par->precision = %d, nbr_len - 1 = %i\n", par->width, par->flag, par->precision, i);
	while (par->flag == 'a' && nbr_len + 2 < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	ret += write(1, "0x", 2);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base(num, 16), ft_strlen(ft_ulltoa_base(num, 16)));
	while (par->flag == '-' && nbr_len + 2 < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}