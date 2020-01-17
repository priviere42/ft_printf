/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_str.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:36:00 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 16:32:04 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		my_printf_str(va_list my_list, t_params *par)
{
	char	*src;
	int		i;
	int		ret;
	int		nul;

    if (par->precision == 0)
        return (0);
	src = va_arg(my_list, char *);
	ret = 0;
	nul = (src == NULL) ? 6 : 0;
	i = ft_strlen(src) + nul;
	while (par->flag != '-' && i++ < par->width)
		ret += write(1, " ", 1);
	if (src == NULL)
		ret += write(1, "(null)", ft_strlen_prec("(null)", par->precision));
	if (par->precision != -1 && src != NULL)
		ret += write(1, src, ft_strlen_prec(src, par->precision));
	else
		ret += write(1, src, ft_strlen(src));
	while (par->flag == '-' && i++ < par->width)
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
	c = malloc(sizeof(unsigned char) * 2);
	c[0] = (unsigned char)va_arg(my_list, int);
	c[1] = '\0';
	while ((par->flag != '-' || c[0] == 0) && i < par->width)
	{
		ret += write(1, " ", 1);
		i++;
	}
	if (par->type == '%')
		ret += write(1, "%", 1);
	else
		ret += write(1, &c[0], 1);
	free(c);
	return (ret);
}
