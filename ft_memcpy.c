/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 15:48:27 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 18:37:45 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*dest;
	char			*sourc;

	dest = (char *)dst;
	sourc = (char *)src;
	if ((src == NULL && dst == NULL) || n == 0)
		return (dst);
	i = 0;
	if (n)
	{
		while (i < n)
		{
			dest[i] = sourc[i];
			i++;
		}
		dst = dest;
	}
	return (dst);
}
