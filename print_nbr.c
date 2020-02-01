/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_nbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:37:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 18:00:47 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		my_printf_nbr(va_list my_list, t_params *par)
{
	int		num;
	int		len;
	int		ret;
	char	*nbr;
	char	c;

	num = va_arg(my_list, int);
	nbr = ft_itoa_base(num, 10);
	c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
	len = (num >= 0) ? ft_strlen(nbr) : ft_strlen(nbr) - 1;
	ret = 0;
	//printf("width = %d, prec = %d, flag = %c\n", par->w, par->p, par->flag);
	if (par->flag == 'a')
	{
		ret += print_width(par, c, block(par->p, nbr));
		ret += (par->p == -2 && par->w >= 0 && num == 0) ? write(1, &c, 1) : 0;
		ret += (num < 0) ? write(1, "-", 1) : 0;
		ret += print_prec(par, len);
		ret += (num == 0 && par->p == 0 && par->w > 0) ? write(1, " ", 1) : 0;
		if (!((par->p == 0 || par->p == -2) && num == 0))
			ret += (num >= 0) ? write(1, nbr, len) : write(1, &nbr[1], len);
	}
	else
		ret += manage_flags(par, num, nbr, block(par->p, nbr));
	free(nbr);
	return (ret);
}

int		my_printf_unbr(va_list my_list, t_params *par)
{
	unsigned int		num;
	int					nbr_len;
	int					ret;
	char				*number;
	char				c;

	num = va_arg(my_list, unsigned int);
	number = ft_ulltoa_base(num, 10);
	nbr_len = ft_strlen(number);
	c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
	ret = 0;
	if (par->flag == 'a')
	{
		ret += print_width(par, c, block(par->p, number));
		ret += (par->p == -2 && par->w >= 0 && num == 0) ? write(1, &c, 1) : 0;
		ret += print_prec(par, nbr_len);
		if (num == 0 && par->p == 0 && par->w > 0)
			ret += write(1, " ", 1);
		if (!((par->p == 0 || par->p == -2) && num == 0))
			ret += write(1, number, ft_strlen(number));
	}
	else
		ret += manage_uflags(par, num, number, block(par->p, number));
	free(number);
	return (ret);
}

int		my_printf_hexa(va_list my_list, t_params *par)
{
	unsigned int		num;
	int					nbr_len;
	int					ret;
	char				*number;
	char				c;

	num = va_arg(my_list, unsigned int);
	number = ft_lltoa_base(num, 16);
	nbr_len = ft_strlen(number);
	c = (par->flag == '0' && par->p <= -1 && par->p != -2) ? '0' : ' ';
	ret = 0;
	if (par->flag == 'a')
	{
		ret += print_width(par, c, block(par->p, number));
		ret += print_prec(par, nbr_len);
		if (num == 0 && (par->p == 0 || par->p == -2) && par->w > 0)
			ret += write(1, " ", 1);
		if (!((par->p == 0 || par->p == -2) && num == 0))
			ret += write(1, number, ft_strlen(number));
	}
	else
		ret += manage_uflags(par, num, number, block(par->p, number));
	free(number);
	return (ret);
}

int		my_printf_majhexa(va_list my_list, t_params *par)
{
	unsigned int		num;
	int					nbr_len;
	int					ret;
	char				*number;
	char				c;

	num = va_arg(my_list, unsigned int);
	number = ft_lltoa_base_maj(num, 16);
	nbr_len = ft_strlen(number);
	c = (par->flag == '0' && par->p <= -1 && par->p != -2) ? '0' : ' ';
	ret = 0;
	if (par->flag == 'a')
	{
		ret += print_width(par, c, block(par->p, number));
		ret += print_prec(par, nbr_len);
		if (num == 0 && (par->p == 0 || par->p == -2) && par->w > 0)
			ret += write(1, " ", 1);
		if (!((par->p == 0 || par->p == -2) && num == 0))
			ret += write(1, number, ft_strlen(number));
	}
	else
		ret += manage_uflags(par, num, number, block(par->p, number));
	free(number);
	return (ret);
}
