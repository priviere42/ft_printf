/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   manage_flags.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 17:34:44 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 17:55:06 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int     print_prec(t_params *par, int nbr_len)
{
    int     i;
    int     ret;

    ret = 0;
    i = nbr_len;
    if (par->p < nbr_len)
        return (0);
    while (i < par->p)
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

int     block(int prec, char *number)
{
    int     len_nbr;

    len_nbr = (*number != '-') ? ft_strlen(number) : ft_strlen(number) - 1;
    if (prec >= len_nbr)
        return ((*number != '-') ? prec : prec + 1);
    return (ft_strlen(number));
}

int     manage_flags(t_params *par, int num, char *number, int block_size)
{
    int                 nbr_len;
	int                 ret;
    char                c;

    c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
    nbr_len = (num >= 0) ? ft_strlen(number) : ft_strlen(number) - 1;
    ret = 0;
    if (par->flag == '-')
    {
        ret += (num < 0) ? write(1, "-", 1) : 0;
        ret += print_prec(par, nbr_len);
        if (num == 0 && par->p == 0 && par->width > 0)
            ret += write(1, " ", 1);
        if (!((par->p == 0 || par->p == -2) && num == 0))
            ret += (num >= 0) ? write(1, number, ft_strlen(number)) : write(1, &number[1], ft_strlen(number) - 1);
        ret += print_width(par, c, block_size);
    }
    else if (par->flag == '0')
    {
        ret += (num < 0 && par->p < 0 && par->p != -2) ? write(1, "-", 1) : 0;
        ret += print_width(par, c, block_size);
        ret += (num < 0 && (par->p >= 0 || par->p == -2)) ? write(1, "-", 1) : 0;
        ret += print_prec(par, nbr_len);
        if (num == 0 && par->p == 0 && par->width > 0)
            ret += write(1, " ", 1);
        if (!((par->p == 0 || par->p == -2) && num == 0))
            ret += (num >= 0) ? write(1, number, ft_strlen(number)) : write(1, &number[1], ft_strlen(number) - 1);
    }
    return (ret);
}

int     manage_uflags(t_params *par, int num, char *number, int block_size)
{
    int                 nbr_len;
	int                 ret;
    char                c;

    c = (par->flag == '0' && par->p == -1) ? '0' : ' ';
    nbr_len = ft_strlen(number);
    ret = 0;
    if (par->flag == '-')
    {
        ret += print_prec(par, nbr_len);
        if (num == 0 && par->p == 0 && par->width > 0)
            ret += write(1, " ", 1);
        if (!((par->p == 0 || par->p == -2) && num == 0))
            ret += write(1, number, ft_strlen(number));
        ret += print_width(par, c, block_size);
    }
    else if (par->flag == '0')
    {
        ret += print_width(par, c, block_size);
        ret += print_prec(par, nbr_len);
        if (num == 0 && par->p == 0 && par->width > 0)
            ret += write(1, " ", 1);
        if (!((par->p == 0 || par->p == -2) && num == 0))
            ret += write(1, number, ft_strlen(number));
    }
    return (ret);
}
