/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 15:12:22 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 18:04:13 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct		s_params
{
	char		flag;
	int			w;
	int			p;
	char		type;
}					t_params;

int					ft_strlen_prec(char *src, int precision);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
char				*ft_strdup(char *s);
int					ft_check_wildcard(va_list my_list, const char *s,
					int i, t_params *par);
int					ft_check_flags(va_list my_list, const char *s,
					int i, t_params *par);
int					treat_flag(const char *src, int i,
					va_list my_list, t_params *par);
int					check_and_treat(const char *s, int i, t_params *par);
int					*my_fct(t_params *par, va_list my_list,
					const char *s, int *r);
long long			ft_pow(long long nb, long long pow);
unsigned long long	ft_pow_ull(unsigned long long nb, unsigned long long p);
t_params			*ft_init_par(t_params *par);
char				*ft_itoa_base(int long long value, long long base);
char				*ft_itoa_base_maj(long long value, long long base);
char				*ft_ulltoa_base(unsigned long long value, int base);
char				*ft_ulltoa_base_maj(unsigned long long value, int base);
char				*ft_lltoa_base(long long value, int base);
char				*ft_lltoa_base_maj(long long value, int base);
int					print_prec(t_params *par, int nbr_len);
int					print_width(t_params *par, char c, int block_size);
int					block(int prec, char *number);
int					manage_flags(t_params *par, int num, char *n, int block);
int					manage_uflags(t_params *par, int num, char *n, int block);
int					my_printf_unbr(va_list my_list, t_params *par);
int					my_printf_nbr(va_list my_list, t_params *par);
int					my_printf_hexa(va_list my_list, t_params *par);
int					my_printf_majhexa(va_list my_list, t_params *par);
int					my_printf_p(va_list my_list, t_params *par);
int					my_printf_str(va_list my_list, t_params *par);
int					my_printf_char(va_list my_list, t_params *par);
int					my_printf_perc(t_params *par);
int					ft_printf(const char *src, ...);

#endif
