/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 14:30:14 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 19:11:38 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int i;
	unsigned int j;

	if (!*needle)
		return ((char *)&haystack[0]);
	j = 0;
	while (haystack[j] != '\0')
	{
		i = 0;
		if (haystack[j] == needle[0])
		{
			while (needle[i] == haystack[j + i]
			&& needle[i] != '\0' && j + i < len)
				i++;
			if (needle[i] == '\0')
				return ((char *)&haystack[j]);
		}
		j++;
	}
	return (0);
}
