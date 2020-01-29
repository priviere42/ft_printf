/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:38:55 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 14:25:43 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_strlen_prec(char *src, int precision)
{
	int i;

	i = 0;
	if (precision >= 0)
		while (src[i] && i < precision)
			i++;
	else
		while (src[i])
			i++;
	return (i);
}

long long				ft_pow(long long nb, long long pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

unsigned long long		ft_pow_ull(unsigned long long nb, unsigned long long p)
{
	if (p == 0)
		return (1);
	else
		return (nb * ft_pow_ull(nb, p - 1));
}

t_params	*ft_init_par(t_params *par)
{
	par = malloc(sizeof(t_params) * 1);
	par->p = -1;
	par->width = -1;
	par->flag = 'a';
	par->type = 'a';
	return (par);
}
