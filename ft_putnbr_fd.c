/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 10:53:23 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 13:06:27 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int mod;
	int div;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = n * -1;
		}
		if (n <= 9)
		{
			n = n + 48;
			write(fd, &n, 1);
		}
		else
		{
			div = n / 10;
			mod = n % 10;
			ft_putnbr_fd(div, fd);
			ft_putnbr_fd(mod, fd);
		}
	}
}
