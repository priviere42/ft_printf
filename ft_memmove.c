/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 18:14:31 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 18:40:32 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*dest;
	char			*sourc;

	dest = (char *)dst;
	sourc = (char *)src;
	if ((dest == NULL && sourc == NULL) || len == 0)
		return (dst);
	i = 0;
	if (dest < sourc)
		dest = ft_memcpy(dst, src, len);
	else
	{
		i = len;
		while (i)
		{
			dest[i - 1] = sourc[i - 1];
			i--;
		}
	}
	dst = dest;
	return (dst);
}
