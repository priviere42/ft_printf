/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 16:18:24 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 15:21:03 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dest;
	unsigned char	*sourc;

	dest = (unsigned char *)dst;
	sourc = (unsigned char *)src;
	i = 0;
	while (sourc[i] != '\0' && i < n && sourc[i] != (unsigned char)c)
	{
		dest[i] = sourc[i];
		i++;
	}
	if (sourc[i] == (unsigned char)c)
	{
		dest[i] = sourc[i];
		dst = dest;
		return ((void *)&dst[i + 1]);
	}
	if (n > i)
		dest[i] = '\0';
	return (NULL);
}
