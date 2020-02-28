/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 16:09:55 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *s, ...)
{
	va_list		my_list;
	t_params	*par;
	int			*ret;
	int			real_ret;

	if (!(ret = malloc(sizeof(int) * 2)))
		return (-1);
	ret[0] = 0;
	ret[1] = 0;
	va_start(my_list, s);
	while (s[ret[0]])
	{
		par = ft_init_par(par);
		ret = my_fct(par, my_list, s, ret);
		ret[0]++;
		free(par);
	}
	real_ret = ret[1];
	free(ret);
	return (real_ret);
}
