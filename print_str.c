/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_str.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:36:00 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 14:28:29 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_i(char *src, t_params *par)
{
	int nul;
	int i;

	nul = ((src == NULL) && par->p != 0) ? 6 : 0;
	if (0 <= par->p && par->p < (int)ft_strlen(src))
		i = ft_strlen_prec(src, par->p);
	else if (par->p == -2 && par->w >= 0 && src != NULL)
		i = 0;
	else
		i = (nul == 6 && (par->p >= 0 || par->p == -2)) ?
		ft_strlen(src) + ft_strlen_prec("(null)", par->p)
		: ft_strlen(src) + nul;
	return (i);
}

int		my_printf_str(va_list my_list, t_params *par)
{
	char	*src;
	int		i;
	int		ret;

	src = va_arg(my_list, char *);
	ret = 0;
	i = ft_get_i(src, par);
	while (par->flag != '-' && i++ < par->w)
		ret += write(1, " ", 1);
	if (src == NULL)
		ret += write(1, "(null)", ft_strlen_prec("(null)", par->p));
	if (par->p != -1 && src != NULL)
		ret += write(1, src, ft_strlen_prec(src, par->p));
	else
		ret += write(1, src, ft_strlen(src));
	while (par->flag == '-' && i++ < par->w)
		ret += write(1, " ", 1);
	return (ret);
}

int		my_printf_char(va_list my_list, t_params *par)
{
	unsigned char	*c;
	int				i;
	int				ret;

	ret = 0;
	i = 1;
	if (!(c = malloc(sizeof(unsigned char) * 2)))
		return (-1);
	c[0] = (unsigned char)va_arg(my_list, int);
	c[1] = '\0';
	while ((par->flag != '-' || c[0] == 0) && i < par->w)
	{
		ret += write(1, " ", 1);
		i++;
	}
	if (par->type == '%')
		ret += write(1, "%", 1);
	else
		ret += write(1, &c[0], 1);
	while (par->flag == '-' && i++ < par->w)
		ret += write(1, " ", 1);
	free(c);
	return (ret);
}

int		my_printf_perc(t_params *par)
{
	int				i;
	int				ret;

	ret = 0;
	i = 1;
	while (par->flag == 'a' && i < par->w)
	{
		ret += write(1, " ", 1);
		i++;
	}
	while (par->flag == '0' && i < par->w)
	{
		ret += write(1, "0", 1);
		i++;
	}
	ret += write(1, "%", 1);
	while (par->flag == '-' && i++ < par->w)
		ret += write(1, " ", 1);
	return (ret);
}
