/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 12:36:44 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 14:54:34 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, const char *set)
{
	int j;

	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == c)
			return (1);
		j++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	char	*str;

	start = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (check(s1[start], set))
		start++;
	while (len - 1 >= 0 && check(s1[len - 1], set))
		len--;
	if (len - start <= 0)
		return (ft_strdup(""));
	if (!(str = ft_substr(s1, start, (len - start))))
		return (0);
	return (str);
}
