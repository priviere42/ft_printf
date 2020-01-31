/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   manage_flags.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 17:34:44 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 15:23:18 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		block(int prec, char *number)
{
	int		len_nbr;

	len_nbr = (*number != '-') ? ft_strlen(number) : ft_strlen(number) - 1;
	if (prec >= len_nbr)
		return ((*number != '-') ? prec : prec + 1);
	return (ft_strlen(number));
}

int		ft_udash(t_params *par, unsigned long long num, char *nbr, int block)
{
	int		ret;
	int		nbr_len;
	char	c;

	c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
	ret = 0;
	nbr_len = ft_strlen(nbr);
	ret += print_prec(par, nbr_len);
	if (num == 0 && par->p == 0 && par->w > 0)
		ret += write(1, " ", 1);
	if (!((par->p == 0 || par->p == -2) && num == 0))
		ret += write(1, nbr, ft_strlen(nbr));
	ret += print_width(par, c, block);
	return (ret);
}

int		ft_dash(t_params *par, int num, char *number, int block_size)
{
	int		ret;
	int		nbr_len;
	char	c;

	c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
	ret = 0;
	nbr_len = (num >= 0) ? ft_strlen(number) : ft_strlen(number) - 1;
	ret += (num < 0) ? write(1, "-", 1) : 0;
	ret += print_prec(par, nbr_len);
	if (num == 0 && par->p == 0 && par->w > 0)
		ret += write(1, " ", 1);
	if (!((par->p == 0 || par->p == -2) && num == 0))
		ret += (num >= 0) ? write(1, number, ft_strlen(number)) :
		write(1, &number[1], ft_strlen(number) - 1);
	ret += print_width(par, c, block_size);
	ret += (par->p == -2 && par->w >= 0 && num == 0) ? write(1, &c, 1) : 0;
	return (ret);
}

int		manage_flags(t_params *par, int num, char *n, int block)
{
	int		nbr_len;
	int		ret;
	char	c;

	c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
	nbr_len = (num >= 0) ? ft_strlen(n) : ft_strlen(n) - 1;
	ret = 0;
	if (par->flag == '-')
		ret += ft_dash(par, num, n, block);
	else if (par->flag == '0')
	{
		ret += (num < 0 && par->p < 0 && par->p != -2) ? write(1, "-", 1) : 0;
		ret += print_width(par, c, block);
		ret += (par->p == -2 && par->w >= 0 && num == 0) ? write(1, &c, 1) : 0;
		ret += (num < 0 && (par->p >= 0 || par->p == -2)) ?
		write(1, "-", 1) : 0;
		ret += print_prec(par, nbr_len);
		if (num == 0 && par->p == 0 && par->w > 0)
			ret += write(1, " ", 1);
		if (!((par->p == 0 || par->p == -2) && num == 0))
			ret += (num >= 0) ? write(1, n, ft_strlen(n)) :
			write(1, &n[1], ft_strlen(n) - 1);
	}
	return (ret);
}

int		manage_uflags(t_params *par, int num, char *n, int block)
{
	int		nbr_len;
	int		ret;
	char	c;

	c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
	nbr_len = ft_strlen(n);
	ret = 0;
	if (par->flag == '-')
		ret += ft_udash(par, num, n, block);
	else if (par->flag == '0')
	{
		ret += print_width(par, c, block);
		ret += print_prec(par, nbr_len);
		if (num == 0 && par->p == 0 && par->w > 0)
			ret += write(1, " ", 1);
		if (!((par->p == 0 || par->p == -2) && num == 0))
			ret += write(1, n, ft_strlen(n));
	}
	return (ret);
}
