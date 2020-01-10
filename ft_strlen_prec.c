/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlen_prec.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 18:04:23 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 16:52:21 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen_prec(char *src, int precision)
{
	int i;

	i = 0;
	if (precision >= 0)
		while (src[i] && i < precision)
			i++;
	else
		while (src[i])
			i++;
	return (i);
}
