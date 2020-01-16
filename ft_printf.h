/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 15:12:22 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 17:30:10 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_params
{
	char		flag;
	int			width;
	int			precision;
}				t_params;

int     ft_strlen_prec(char *src, int precision);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	*ft_itoa_base(int value, int base);
char	*ft_itoa_base_maj(int value, int base);
char	*ft_ulltoa_base(unsigned long long value, int base);
char	*ft_ulltoa_base_maj(unsigned long long value, int base);
int 	ft_printf(const char *src, ...);

#endif
