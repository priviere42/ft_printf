/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_nbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:37:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 16:18:57 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int my_printf_unbr(va_list my_list, t_params *par)
{
    unsigned long long  num;
	int                 i;
	int                 nbr_len;
	int                 ret;
    char                *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base(num, 10);
	nbr_len = ft_strlen(number);
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len++ < par->width
    && par->precision < par->width)
		ret += write(1, " ", 1);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}

int my_printf_nbr(va_list my_list, t_params *par)
{
    int                 num;
	int                 nbr_len;
	int                 ret;
    char                *number;

	ret = 0;
    num = va_arg(my_list, int);
    number = ft_itoa_base(num, 10);
    nbr_len = (num >= 0) ? ft_strlen(number) : ft_strlen(number) - 1;
    if (par->width > par->precision && par->precision <= (int)ft_strlen(number))
	{
        if (num >= 0)
        {    
            while (par->flag == 'a' && nbr_len++ < par->width)
		        ret += write(1, " ", 1);
        }
        else
            while (par->flag == 'a' && ++nbr_len < par->width)
		        ret += write(1, " ", 1);
    }
    if (par->width > par->precision && par->precision > (int)ft_strlen(number))
 	{
        while (par->flag != '-' && ret < par->width - par->precision)
            ret += write(1, " ", 1);
    }
    if (par->precision > 0)
    {
        ret += (num < 0) ? write(1, "-", 1) : 0;
        while (par->flag != '-' && nbr_len++ < par->precision)
		    ret += write(1, "0", 1);       
    }
    if (num < 0 && par->precision <= 0)
         ret += write(1, "-", 1);
    if (num >= 0)
        while (par->flag == '0' && nbr_len++ < par->width)
		    ret += write(1, "0", 1);
    else
       while (par->flag == '0' && ++nbr_len < par->width)
		    ret += write(1, "0", 1);
    ret += (num >= 0) ? write(1, number, ft_strlen(number)) : write(1, &number[1], ft_strlen(number) - 1);
	while (par->flag == '-' && ret < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}

int	my_printf_hexa(va_list my_list, t_params *par)
{
    unsigned long long  num;
	int                 i;
	int                 nbr_len;
	int                 ret;
    char                *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base(num, 16);
	nbr_len = ft_strlen(number);
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len++ < par->width
    && par->precision < par->width)
		ret += write(1, " ", 1);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}

int	my_printf_majhexa(va_list my_list, t_params *par)
{
    unsigned long long num;
	int i;
	int nbr_len;
	int ret;
    char *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base_maj(num, 16);
	nbr_len = ft_strlen(number);
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len++ < par->width
    && par->precision < par->width)
		ret += write(1, " ", 1);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}

int		my_printf_p(va_list my_list, t_params *par)
{
    unsigned long long num;
	int i;
	int nbr_len;
	int ret;
    char *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base(num, 16);
	nbr_len = ft_strlen(number) + 2;
	i = nbr_len + 1;
	while (par->flag == 'a' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
	ret += write(1, "0x", 2);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}
