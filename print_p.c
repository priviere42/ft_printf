/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_p.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 10:48:26 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 10:48:49 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_p(t_params *par, unsigned long long num)
{
	int		ret;
	int		nbr_len;
	char	*number;
	int		i;

	ret = 0;
	number = ft_ulltoa_base(num, 16);
	nbr_len = ft_strlen(number) + 2;
	i = nbr_len + 1;
	while (par->flag == 'a' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
	ret += write(1, "0x", 2);
	while (par->p > 0 && ++i < par->p && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->p == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->p == 0 && num == 0))
		ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
	free(number);
	return (ret);
}

int		my_printf_p(va_list my_list, t_params *par)
{
	unsigned long long	num;
	int					ret;

	ret = 0;
	num = va_arg(my_list, unsigned long long);
	if ((void *)num == NULL && par->p == -2)
	{
		while (ret < par->width - 2)
			ret += write(1, " ", 1);
		return (ret += write(1, "0x", 2));
	}
	ret += write_p(par, num);
	return (ret);
}
