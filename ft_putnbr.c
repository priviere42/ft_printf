/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 17:58:11 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 17:59:16 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	ft_putnbr(int n)
{
	int mod;
	int div;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = n * -1;
		}
		if (n <= 9)
		{
			n = n + 48;
			write(1, &n, 1);
		}
		else
		{
			div = n / 10;
			mod = n % 10;
			ft_putnbr(div);
			ft_putnbr(mod);
		}
	}
}