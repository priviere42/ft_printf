/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_w_or_p.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 18:38:36 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 18:44:59 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_prec(t_params *par, int nbr_len)
{
	int i;
	int	ret;

	ret = 0;
	i = nbr_len;
	if (par->p < nbr_len)
		return (0);
	while (i < par->p)
	{
		ret += write(1, "0", 1);
		i++;
	}
	return (ret);
}

int		print_width(t_params *par, char c, int block_size)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if (par->width < block_size)
		return (0);
	while (i != par->width - block_size)
	{
		ret += write(1, &c, 1);
		i++;
	}
	return (ret);
}
