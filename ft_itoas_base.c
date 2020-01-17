/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoas_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 18:29:19 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 16:29:55 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

long long				ft_pow(long long nb, long long pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

unsigned long long		ft_pow_ull(unsigned long long nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow_ull(nb, pow - 1));
}

char					*ft_itoa_base(long long value, long long base)
{
	long long			i;
	char		        *nbr;
	long long			neg;

	i = 1;
	neg = 0;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value = value * -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		nbr[i + neg] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}

char					*ft_itoa_base_maj(long long value, long long base)
{
	int		i;
	char	*nbr;
	int		neg;

	i = 1;
	neg = 0;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value = value * -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		nbr[i + neg] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}

char					*ft_ulltoa_base(unsigned long long value, int base)
{
	int		i;
	char	*nbr;

	i = 1;
	if (value == 2147483647)
		return ("2147483647");
	while (ft_pow_ull(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	return (nbr);
}

char					*ft_ulltoa_base_maj(unsigned long long value, int base)
{
	int		i;
	char	*nbr;

	i = 1;
	if (value == 2147483647)
		return ("2147483647");
	while (ft_pow_ull(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		value = value / base;
	}
	return (nbr);
}
