/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 15:12:22 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 17:55:07 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct	s_params
{
	char		flag;
	int			width;
	int			p;
	char		type;
}				t_params;

int     	ft_strlen_prec(char *src, int precision);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
t_params	*ft_init_par(t_params *par);
char		*ft_itoa_base(int long long value, long long base);
char		*ft_itoa_base_maj(long long value, long long base);
char		*ft_ulltoa_base(unsigned long long value, int base);
char		*ft_ulltoa_base_maj(unsigned long long value, int base);
int         print_prec(t_params *par, int nbr_len);
int         print_width(t_params *par, char c, int block_size);
int         block(int prec, char *number);
int         manage_flags(t_params *par, int num, char *number, int block_size);
int         manage_uflags(t_params *par, int num, char *number, int block_size);
int 		my_printf_unbr(va_list my_list, t_params *par);
int 		my_printf_nbr(va_list my_list, t_params *par);
int			my_printf_hexa(va_list my_list, t_params *par);
int			my_printf_majhexa(va_list my_list, t_params *par);
int			my_printf_p(va_list my_list, t_params *par);
int 		my_printf_str(va_list my_list, t_params *par);
int 		my_printf_char(va_list my_list, t_params *par);
int		    my_printf_perc(t_params *par);


int 		ft_printf(const char *src, ...);

#endif
