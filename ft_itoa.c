/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/18 18:29:19 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 16:36:20 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static long	ft_nblen(long nb)
{
	long	len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*ft_check_exceptions(long nb, char *str)
{
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	return (0);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nb;

	nb = n;
	len = ft_nblen(nb);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	if (!ft_check_exceptions(nb, str))
	{
		if (nb < 0)
		{
			nb = nb * -1;
			str[0] = '-';
		}
		while (nb > 0)
		{
			str[len - 1] = (nb % 10) + 48;
			nb = nb / 10;
			len--;
		}
	}
	return (str);
}
