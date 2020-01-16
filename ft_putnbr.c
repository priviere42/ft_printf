/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 17:58:11 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 16:18:20 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "ft_printf.h"

int		ft_putnbr(int n)
{
	int mod;
	int div;
	static int ret = 0;

	if (n == -2147483648)
		ret += write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			ret += write(1, "-", 1);
			n = n * -1;
		}
		if (n <= 9)
		{
			n = n + 48;
			ret += write(1, &n, 1);
		}
		else
		{
			div = n / 10;
			mod = n % 10;
			ft_putnbr(div);
			ft_putnbr(mod);
		}
	}
	return (ret);
}
