/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_nbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 10:37:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 14:07:06 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int my_printf_unbr(va_list my_list, t_params *par)
{
    unsigned long long  num;
	int                 i;
	int                 nbr_len;
	int                 ret;
    char                *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base(num, 10);
	nbr_len = ft_strlen(number);
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len++ < par->width
    && par->precision < par->width)
		ret += write(1, " ", 1);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}

// int my_printf_nbr(va_list my_list, t_params *par)
// {
//     int                 num;
// 	int                 nbr_len;
// 	int                 ret;
//     char                *number;
//     int                 i;

// 	ret = 0;
//     num = va_arg(my_list, int);
//     number = ft_itoa_base(num, 10);
//     nbr_len = (num >= 0) ? ft_strlen(number) : ft_strlen(number) - 1;
//  //   printf("nbrlen = %d\n", nbr_len);
//     if (par->width > par->precision && par->precision <= nbr_len)
// 	{
//         if (num >= 0)
//         {   
//            // printf("flag : %c, nbrlen : %d, width : %d\n", par->flag, nbr_len, par->width);
//             while (par->flag == 'a' && nbr_len < par->width)
// 		    {
//                 ret += write(1, " ", 1);
//                 nbr_len++;
//             }
//           //  printf("flag : %c, nbrlen : %d, width : %d\n", par->flag, nbr_len, par->width);
//         }
//         else
//             while (par->flag == 'a' && nbr_len < par->width - 1) //je swappe le - avec - 1
// 		    {
//                 ret += write(1, " ", 1);
//                 nbr_len++;
//             }
//     }
//     if (par->width > par->precision && par->precision > nbr_len)
//  	{
//         i = 0;
//         while (par->flag != '-' && i < par->width - par->precision)
//         {
//             ret += write(1, " ", 1);
//             i++;
//         }
//     }
//     if (par->precision > 0)
//     {
//         ret += (num < 0) ? write(1, "-", 1) : 0;
//         while (par->flag != '-' && nbr_len++ < par->precision)
// 		    ret += write(1, "0", 1);       
//     }
//     if (num < 0 && par->precision <= 0)
//          ret += write(1, "-", 1);
//     if (num >= 0)
//     {
//         while (par->flag == '0' && nbr_len < par->width)
// 		{    
//             ret += write(1, "0", 1);
//             nbr_len++;
//         }
//         i = 0;
//         while (par->flag == '-' && par->precision >= 0 && i++ < par->precision - nbr_len)
//             ret += write(1, "0", 1);
//     }
//     else
//     {
//         while (par->flag == '0' && ++nbr_len < par->width)
// 		    ret += write(1, "0", 1);
//         i = 0;
//         while (par->flag == '-' && par->precision >= 0 && i++ < par->precision - nbr_len)
//             ret += write(1, "0", 1);
//     }
//     if (num == 0 && (par->precision == 0 || par->precision == -2))
//     {
//      //   printf("flag : %c, nbrlen : %d, width : %d", par->flag, nbr_len, par->width);
//         while (par->flag == 'a' && nbr_len++ < par->width + 1)
// 		    ret += write(1, " ", 1);
//         return (ret);
//     } 
//     ret += (num >= 0) ? write(1, number, ft_strlen(number)) : write(1, &number[1], ft_strlen(number) - 1);
// 	while (par->flag == '-' && ret < par->width)
// 		ret += write(1, " ", 1);
//     free(number);
// 	return (ret);
// }

int     print_prec(t_params *par, int nbr_len)
{
    int     i;
    int     ret;

    ret = 0;
    i = nbr_len;
    if (par->precision < nbr_len)
        return (0);
    while (i < par->precision)
    {
        ret += write(1, "0", 1);
        i++;
    }
    return (ret);
}

int     print_width(t_params *par, char c, int block_size)
{
    int     i;
    int     ret;

    ret = 0;
    i = 0;
    if (par->width < block_size)
        return (0);
    while (i != par->width - block_size)
    {
        ret += write(1, &c, 1);
        i++;
    }
    return (ret);
}

int     calc_block_size(int prec, char *number)
{
    int     len_nbr;

    len_nbr = (*number != '-') ? ft_strlen(number) : ft_strlen(number) - 1;
    if (prec >= len_nbr)
        return ((*number != '-') ? prec : prec + 1);
    return (ft_strlen(number));
}

int my_printf_nbr(va_list my_list, t_params *par)
{
     int                 num;
	int                 nbr_len;
	int                 ret;
    char                *number; 
    char                c;
    int                 block_size;

    num = va_arg(my_list, int);
    number = ft_itoa_base(num, 10);
    block_size = calc_block_size(par->precision, number);
    nbr_len = (num >= 0) ? ft_strlen(number) : ft_strlen(number) - 1;
    c = (par->flag == '0' && par->precision == -1) ? '0' : ' ';
    ret = 0;
    if (par->flag == '-')
    {
        ret += (num < 0) ? write(1, "-", 1) : 0;
        ret += print_prec(par, nbr_len);
        if (num == 0 && par->precision == 0 && par->width > 0)
            ret += write(1, " ", 1);
        if (!(par->precision == 0 && num == 0))
            ret += (num >= 0) ? write(1, number, ft_strlen(number)) : write(1, &number[1], ft_strlen(number) - 1);
        ret += print_width(par, c, block_size);
    }
    else if (par->flag == '0')
    {
        ret += (num < 0 && par->precision < 0 && par->precision != -2) ? write(1, "-", 1) : 0;
        ret += print_width(par, c, block_size);
        ret += (num < 0 && (par->precision >= 0 || par->precision == -2)) ? write(1, "-", 1) : 0;
        ret += print_prec(par, nbr_len);
        if (num == 0 && par->precision == 0 && par->width > 0)
            ret += write(1, " ", 1);
        if (!(par->precision == 0 && num == 0))
            ret += (num >= 0) ? write(1, number, ft_strlen(number)) : write(1, &number[1], ft_strlen(number) - 1);
    }
    else
    {
        ret += print_width(par, c, block_size);
        ret += (num < 0) ? write(1, "-", 1) : 0;
        ret += print_prec(par, nbr_len);
    //    printf("\npar->width = %d, par->flag = %c, par->precision = %d, num = %d\n", par->width, par->flag, par->precision, num);
        if (num == 0 && par->precision == 0 && par->width > 0)
            ret += write(1, " ", 1);
        if (!(par->precision == 0 && num == 0))
            ret += (num >= 0) ? write(1, number, ft_strlen(number)) : write(1, &number[1], ft_strlen(number) - 1);
    }
    return (ret);
}

int	my_printf_hexa(va_list my_list, t_params *par)
{
    unsigned long long  num;
	int                 i;
	int                 nbr_len;
	int                 ret;
    char                *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base(num, 16);
	nbr_len = ft_strlen(number);
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len++ < par->width
    && par->precision < par->width)
		ret += write(1, " ", 1);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}

int	my_printf_majhexa(va_list my_list, t_params *par)
{
    unsigned long long num;
	int i;
	int nbr_len;
	int ret;
    char *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base_maj(num, 16);
	nbr_len = ft_strlen(number);
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len++ < par->width
    && par->precision < par->width)
		ret += write(1, " ", 1);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}

int		my_printf_p(va_list my_list, t_params *par)
{
    unsigned long long num;
	int i;
	int nbr_len;
	int ret;
    char *number;

	ret = 0;
    num = va_arg(my_list, unsigned long long);
    number = ft_ulltoa_base(num, 16);
	nbr_len = ft_strlen(number) + 2;
	i = nbr_len + 1;
	while (par->flag == 'a' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
	ret += write(1, "0x", 2);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write(1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write(1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, number, ft_strlen(number));
	while (par->flag == '-' && nbr_len++ < par->width)
		ret += write(1, " ", 1);
    free(number);
	return (ret);
}
