/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putunbr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 17:58:11 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 16:18:26 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "ft_printf.h"

int		ft_putunbr(int n)
{
	int mod;
	int div;
	static int ret = 0;

    if (n == 0)
        ret += write(1, "0", 1);
    if ((unsigned int)n > 0)
	{
		if ((unsigned int)n <= 9)
		{
			n = (unsigned int)n + 48;
			ret += write(1, &n, 1);
		}
		else
		{
			div = (unsigned int)n / 10;
			mod = (unsigned int)n % 10;
			ft_putnbr(div);
			ft_putnbr(mod);
		}
	}
	return (ret);
}
