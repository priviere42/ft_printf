/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 14:25:12 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 11:52:49 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void		*ft_free(char **res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (0);
}

static char		*ft_fill(char *dst, char *src, int len)
{
	int i;

	i = 0;
	while (i != len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static int		ft_count_words(char *str, char c)
{
	int i;
	int word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c && str[i])
				i++;
		}
		if (str[i] != c && str[i])
		{
			while (str[i] != c && str[i])
				i++;
			word++;
		}
	}
	return (word);
}

static char		*ft_str(char **res, char *str, char c, int i)
{
	int k;

	k = 0;
	if (str[k] != c)
	{
		while (str[k] != c && str[k])
			k++;
		if (!(res[i] = ft_calloc(k + 1, sizeof(char))))
			return (NULL);
		while (*str == c && *str)
			str++;
		res[i] = ft_fill(res[i], str, k);
		str += k;
	}
	return (str);
}

char			**ft_split(char const *s, char c)
{
	char	**res;
	char	*str;
	int		i;
	int		words;

	if (!s)
		return (NULL);
	str = (char *)s;
	words = ft_count_words(str, c);
	if (!(res = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	while (i != words)
	{
		while (*str == c)
			str++;
		if (!(str = ft_str(res, str, c, i)))
			return (ft_free(res, i - 1));
		i++;
	}
	res[i] = NULL;
	return (res);
}
