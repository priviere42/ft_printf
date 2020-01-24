/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:38:55 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 18:42:11 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}

int			ft_strlen_prec(char *src, int precision)
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

int			ft_atoi(const char *str)
{
	long	i;
	long	a;
	int		sign;

	sign = 1;
	i = 0;
	a = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - '0');
		i++;
	}
	return (a * sign);
}

t_params	*ft_init_par(t_params *par)
{
	par = malloc(sizeof(t_params) * 1);
	par->p = -1;
	par->width = -1;
	par->flag = 'a';
	par->type = 'a';
	return (par);
}
