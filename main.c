/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 19:19:50 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "ft_printf.h"

/*
Ecrire au fur et a mesure le texte puis les flags%_ puis text puis flags%_ ...
Traiter le %
done					: % : pour afficher un % si precede %

Recuperer les flags :
					: 0 : Suivi de la width : nombre en str donne le minimum de CARACTERES
						  à afficher. Si precision est donnée avec d (done), i, u, o, x, X le flag est ignoré
						  printf("%00d\n", 0);-> outputs '0' (done)
done					: - : Aligne a gauche dans la width
done						  Prioritaire sur le 0 si les deux flags sont présents

Recuperer la width :
done					: entier decimal : (si negatif passe en positif et met le flag a '-') nombre de caracteres a afficher
done						  ajoute des ' ' a gauche ou droite si '-' si trop grand
						  ne tronque pas les nombres originaux
					: * : largeur de champs ou precision ou les deux indiqué par *

recuperer la precision :
					: . : Suivi d'un nombre en str (ne peut pas etre negatif) donne le nombre minimum de CHIFFRES
						  a afficher pour d (done), i, o, u, x, X (si pas de chiffre precision a 0)
done						  nombre de char max a afficher pour s 
done						  printf("%.0d", 0);  -> no output
done						  printf("%.0d", 10); -> outputs 10
					: * : largeur de champs ou precision ou les deux indiqué par *

recuperer les types de conversion:

	TYPE LETTRES (Precision non specifiée : Minimum de nombres qui doivent apparaitre)
				 (Si precision donnée aligner sur la droite avec zero a gauche)
done				: c : Int argument convertis en (unsigned char)
done						  Si c = '\0' il faut forcer l'affichage du '\0'
done					: s : Chaine de caractere sans le \0 en (char *)
					: p : Affiche en hexadecimal le pointeur void * casté en (unsigned long long)

	TYPE NOMBRES
done					: d : int signed decimal (int)
done					: i : integer signed decimal (int)
done					: u : unsigned decimal (unsigned int)
done					: x : unsigned hexadecimal (unsigned int)
done					: X : unsigned hexadecimal en MAJUSCULE (unsigned int)
*/

// faire un bon makefile
// faire passer des tests

int my_printf_str(va_list my_list, t_params *par)
{
    char *src = va_arg(my_list, char *);
	int i;
	int ret;
	int nul;

	ret = 0;
	nul = (src == NULL) ? 6 : 0;
	i = ft_strlen(src);
	while (par->flag != '-' && i + nul < par->width)
	{
		ret += write(1, " ", 1);
		i++;
	}
	if (src == NULL)
		ret += write(1, "(null)", ft_strlen_prec("(null)", par->precision));
	if (par->precision != -1 && src != NULL)
    	ret += write(1, src, ft_strlen_prec(src, par->precision));
	else
		ret += write(1, src, ft_strlen(src));
	while (par->flag == '-' && i + nul < par->width)
	{
		ret += write(1, " ", 1);
		i++;
	}
	return (ret);
}

int my_printf_char(va_list my_list, t_params *par)
{
    unsigned char *c;
    int i;
	int ret;

	ret = 0;
	i = 1;
	c = malloc(sizeof(unsigned char) * 2);
    c[0] = (unsigned char)va_arg(my_list, int);
    c[1] = '\0';
	while ((par->flag != '-' || c[0] == 0) && i < par->width)
	{
		ret += write(1, " ", 1);
		i++;
	}
	if (par->type == '%')
    	ret += write(1, "%", 1);
    else
    	ret += write(1, &c[0], 1);
	return (ret);
}

int my_printf_unbr(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base(num, 10));
	i = nbr_len - 1;
	{
		while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
		{
			ret += write(1, " ", 1);
			nbr_len++;
		}
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base(num, 10), ft_strlen(ft_ulltoa_base(num, 10)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int my_printf_nbr(va_list my_list, t_params *par)
{
    int num = va_arg(my_list, int);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_itoa_base(num, 10));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_itoa_base(num, 10), ft_strlen(ft_itoa_base(num, 10)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int	my_printf_hexa(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base(num, 16));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base(num, 16), ft_strlen(ft_ulltoa_base(num, 16)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int	my_printf_majhexa(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base_maj(num, 16));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base_maj(num, 16), ft_strlen(ft_ulltoa_base_maj(num, 16)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int		my_printf_p(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;
	int ret;

	ret = 0;
	nbr_len = ft_strlen(ft_ulltoa_base(num, 16));
	i = nbr_len - 1;
//	printf("\npar->width = %d, par->flag = %c, par->precision = %d, nbr_len - 1 = %i\n", par->width, par->flag, par->precision, i);
	while (par->flag == 'a' && nbr_len + 2 < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	ret += write(1, "0x", 2);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		ret += write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		ret += write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ret += write(1, ft_ulltoa_base(num, 16), ft_strlen(ft_ulltoa_base(num, 16)));
	while (par->flag == '-' && nbr_len + 2 < par->width)
	{
		ret += write(1, " ", 1);
		nbr_len++;
	}
	return (ret);
}

int 	ft_check_wildcard(va_list my_list, const char *src, int i, t_params *par)
{
	int num;
	
	if (src[i] == '*')
	{
		if ((num = va_arg(my_list, int)) < 0)
		{
			par->width = -1 * num;
			par->flag = '-';
		}
		else
			par->width = num;
		i++;
	}
	if (src[i] == '.' && src[i + 1] == '*')
	{
		par->precision = va_arg(my_list, int);
		if (par->precision < 0)
		{
			par->precision = -1 * par->precision;
			if (par->width == -1)
				par->flag = '-';
		}
		i = i + 2;
	}
	return (i);
}

int	ft_check_flags(va_list my_list, const char *src, int i, t_params *par)
{
	if (src[i] == '0' || src[i] == '-')
	{
		par->flag = (src[i] == '0') && (src[i + 1] == '-') ? '-' : src[i];
		if (((src[i] == '0') && (src[i + 1] == '-'))
		|| ((src[i] == '-') && (src[i + 1] == '0')))
			i++;
		i++;
	}
	if (src[i] >= '0' && src[i] <= '9')
	{	
		par->width = ft_atoi(&src[i]);
		while (src[i] && (src[i] >= '0' && src[i] <= '9'))
			i++;
	}
	i = ft_check_wildcard(my_list, src, i, par);
	if ((src[i] == '.' && src[i + 1]))
		par->precision = ft_atoi(&src[++i]);
	if ((par->flag != 'a') && src[i + 1] >= '0' && src[i + 1] <= '9' && par->precision == -1)
		par->width = ft_atoi(&src[i++]);
	while (src[i] && (src[i] >= '0' && src[i] <= '9'))
		i++;
//	printf("\npar->width = %d, par->flag = %c, par->precision = %d, index = %i\n", par->width, par->flag, par->precision, i);
	return (i);
}

t_params	*ft_init_par(t_params *par)
{
	par = malloc(sizeof(t_params) * 1);
	par->precision = -1;
	par->width = -1;
	par->flag = 'a';
	return (par);
}

// traiter tout ce qu'il y a apres le %, jusqua un des flags s, c, d, p etc...
int ft_printf(const char *src, ...)
{
    va_list my_list;
	t_params *par;
    int i;
	int ret;

	ret = 0;
    va_start(my_list, src);
    i = 0;
    while (src[i])
    {
		par = ft_init_par(par);
        if (src[i] != 0 && i != 0 && src[i - 1] == '%')
        {
			i = ft_check_flags(my_list, src, i, par);
	//		printf("\npar->width = %d, par->flag = %c, par->precision = %d, index = %d, src[i] = %c\n", par->width, par->flag, par->precision, i, src[i]);
            if (src[i] == 'd' || src[i] == 'i')
                ret += my_printf_nbr(my_list, par);
            if (src[i] == 's')
                ret += my_printf_str(my_list, par);
            if (src[i] == 'c')
                ret += my_printf_char(my_list, par);
            if (src[i] == '%')
			{
				par->type = '%';
                ret += my_printf_char(my_list, par);
			}
			if (src[i] == 'u')
				ret += my_printf_unbr(my_list, par);
			if (src[i] == 'X')
				ret += my_printf_majhexa(my_list, par);
			if (src[i] == 'x')
				ret += my_printf_hexa(my_list, par);
			if (src[i] == 'p')
				ret += my_printf_p(my_list, par);
            else if ((src[i] != '%' &&
			(src[i] != 's' && src[i] != 'c' && src[i] != 'd' && src[i] != 'i' && src[i] != 'u' && src[i] != 'x' && src[i] != 'X')))
                ret += write(1, &src[i], 1);
        }
        else if (src[i] != '%')
            ret += write(1, &src[i], 1);
        i++;
		free(par);
    }
	return (ret);
}


// #include <limits.h>
// int main()
// {
// //	char* tutu = "sa";
// 	int ret = 0;
// 	int ret_printf = 0;

//     ret = ft_printf("ft_printf : |%-46c|\n", 0);
// 	printf("Retour de mon printf :%d\n", ret);
//     ret_printf = printf("printf    : |%-46c|\n", 0);
// 	printf("Retour du vrai printf :%d\n", ret_printf);
// 	return (0);
// }
